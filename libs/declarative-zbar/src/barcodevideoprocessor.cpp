/*
 * barcodevideoprocessor.cpp
 *
 * Copyright (C) 2011  Imogen Software Carsten Valdemar Munk
 *
 * Author: Tom Swindell - <t.swindell@rubyx.co.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.#ifndef GRANDEWEBRUNTIME_H
 *
 */
#include "common.h"
#include "barcodevideoprocessor.h"

#include <stdint.h>
#include "QZBarThread.h"

#include <QImage>
#include <QVideoSurfaceFormat>

#ifdef  __ARM_NEON__
/*
* ARM NEON optimized implementation of UYVY -> RGB16 convertor
*/
static void uyvy422_to_rgb16_line_neon (uint8_t * dst, const uint8_t * src, int n)
{
     /* and this is the NEON code itself */
     static __attribute__ ((aligned (16))) uint16_t acc_r[8] = {
       22840, 22840, 22840, 22840, 22840, 22840, 22840, 22840,
     };
     static __attribute__ ((aligned (16))) uint16_t acc_g[8] = {
       17312, 17312, 17312, 17312, 17312, 17312, 17312, 17312,
     };
     static __attribute__ ((aligned (16))) uint16_t acc_b[8] = {
       28832, 28832, 28832, 28832, 28832, 28832, 28832, 28832,
     };
     /*
      * Registers:
      * q0, q1 : d0, d1, d2, d3  - are used for initial loading of YUV data
      * q2     : d4, d5          - are used for storing converted RGB data
      * q3     : d6, d7          - are used for temporary storage
      *
      * q6     : d12, d13        - are used for converting to RGB16
      * q7     : d14, d15        - are used for storing RGB16 data
      * q4-q5 - reserved
      *
      * q8, q9 : d16, d17, d18, d19  - are used for expanded Y data
      * q10    : d20, d21
      * q11    : d22, d23
      * q12    : d24, d25
      * q13    : d26, d27
      * q13, q14, q15            - various constants (#16, #149, #204, #50, #104, #154)
      */
     asm volatile (".macro convert_macroblock size\n"
         /* load up to 16 source pixels in UYVY format */
         ".if \\size == 16\n"
         "pld [%[src], #128]\n"
         "vld1.32 {d0, d1, d2, d3}, [%[src]]!\n"
         ".elseif \\size == 8\n"
         "vld1.32 {d0, d1}, [%[src]]!\n"
         ".elseif \\size == 4\n"
         "vld1.32 {d0}, [%[src]]!\n"
         ".elseif \\size == 2\n"
         "vld1.32 {d0[0]}, [%[src]]!\n"
         ".else\n" ".error \"unsupported macroblock size\"\n" ".endif\n"
         /* convert from 'packed' to 'planar' representation */
         "vuzp.8      d0, d1\n"    /* d1 - separated Y data (first 8 bytes) */
         "vuzp.8      d2, d3\n"    /* d3 - separated Y data (next 8 bytes) */
         "vuzp.8      d0, d2\n"    /* d0 - separated U data, d2 - separated V data */
         /* split even and odd Y color components */
         "vuzp.8      d1, d3\n"    /* d1 - evenY, d3 - oddY */
         /* clip upper and lower boundaries */
         "vqadd.u8    q0, q0, q4\n"
         "vqadd.u8    q1, q1, q4\n"
         "vqsub.u8    q0, q0, q5\n"
         "vqsub.u8    q1, q1, q5\n"
         "vshr.u8     d4, d2, #1\n"    /* d4 = V >> 1 */
         "vmull.u8    q8, d1, d27\n"       /* q8 = evenY * 149 */
         "vmull.u8    q9, d3, d27\n"       /* q9 = oddY * 149 */
         "vld1.16     {d20, d21}, [%[acc_r], :128]\n"      /* q10 - initialize accumulator for red */
         "vsubw.u8    q10, q10, d4\n"      /* red acc -= (V >> 1) */
         "vmlsl.u8    q10, d2, d28\n"      /* red acc -= V * 204 */
         "vld1.16     {d22, d23}, [%[acc_g], :128]\n"      /* q11 - initialize accumulator for green */
         "vmlsl.u8    q11, d2, d30\n"      /* green acc -= V * 104 */
         "vmlsl.u8    q11, d0, d29\n"      /* green acc -= U * 50 */
         "vld1.16     {d24, d25}, [%[acc_b], :128]\n"      /* q12 - initialize accumulator for blue */
         "vmlsl.u8    q12, d0, d30\n"      /* blue acc -= U * 104 */
         "vmlsl.u8    q12, d0, d31\n"      /* blue acc -= U * 154 */
         "vhsub.s16   q3, q8, q10\n"       /* calculate even red components */
         "vhsub.s16   q10, q9, q10\n"      /* calculate odd red components */
         "vqshrun.s16 d0, q3, #6\n"        /* right shift, narrow and saturate even red components */
         "vqshrun.s16 d3, q10, #6\n"       /* right shift, narrow and saturate odd red components */
         "vhadd.s16   q3, q8, q11\n"       /* calculate even green components */
         "vhadd.s16   q11, q9, q11\n"      /* calculate odd green components */
         "vqshrun.s16 d1, q3, #6\n"        /* right shift, narrow and saturate even green components */
         "vqshrun.s16 d4, q11, #6\n"       /* right shift, narrow and saturate odd green components */
         "vhsub.s16   q3, q8, q12\n"       /* calculate even blue components */
         "vhsub.s16   q12, q9, q12\n"      /* calculate odd blue components */
         "vqshrun.s16 d2, q3, #6\n"        /* right shift, narrow and saturate even blue components */
         "vqshrun.s16 d5, q12, #6\n"       /* right shift, narrow and saturate odd blue components */
         "vzip.8      d0, d3\n"    /* join even and odd red components */
         "vzip.8      d1, d4\n"    /* join even and odd green components */
         "vzip.8      d2, d5\n"    /* join even and odd blue components */
         "vshll.u8     q7, d0, #8\n" //red
         "vshll.u8     q6, d1, #8\n" //greed
         "vsri.u16   q7, q6, #5\n"
         "vshll.u8     q6, d2, #8\n" //blue
         "vsri.u16   q7, q6, #11\n" //now there is rgb16 in q7
         ".if \\size == 16\n"
         "vst1.16 {d14, d15}, [%[dst]]!\n"
         //"vst3.8  {d0, d1, d2}, [%[dst]]!\n"
         "vshll.u8     q7, d3, #8\n" //red
         "vshll.u8     q6, d4, #8\n" //greed
         "vsri.u16   q7, q6, #5\n"
         "vshll.u8     q6, d5, #8\n" //blue
         "vsri.u16   q7, q6, #11\n" //now there is rgb16 in q7
         //"vst3.8  {d3, d4, d5}, [%[dst]]!\n"
         "vst1.16 {d14, d15}, [%[dst]]!\n"
         ".elseif \\size == 8\n"
         "vst1.16 {d14, d15}, [%[dst]]!\n"
         //"vst3.8  {d0, d1, d2}, [%[dst]]!\n"
         ".elseif \\size == 4\n"
         "vst1.8 {d14}, [%[dst]]!\n"
         ".elseif \\size == 2\n"
         "vst1.8 {d14[0]}, [%[dst]]!\n"
         "vst1.8 {d14[1]}, [%[dst]]!\n"
         ".else\n"
         ".error \"unsupported macroblock size\"\n"
         ".endif\n"
         ".endm\n"
         "vmov.u8     d8, #15\n"  /* add this to U/V to saturate upper boundary */
         "vmov.u8     d9, #20\n"   /* add this to Y to saturate upper boundary */
         "vmov.u8     d10, #31\n"  /* sub this from U/V to saturate lower boundary */
         "vmov.u8     d11, #36\n"  /* sub this from Y to saturate lower boundary */
         "vmov.u8     d26, #16\n"
         "vmov.u8     d27, #149\n"
         "vmov.u8     d28, #204\n"
         "vmov.u8     d29, #50\n"
         "vmov.u8     d30, #104\n"
         "vmov.u8     d31, #154\n"
         "subs        %[n], %[n], #16\n"
         "blt         2f\n"
         "1:\n"
         "convert_macroblock 16\n"
         "subs        %[n], %[n], #16\n"
         "bge         1b\n"
         "2:\n"
         "tst         %[n], #8\n"
         "beq         3f\n"
         "convert_macroblock 8\n"
         "3:\n"
         "tst         %[n], #4\n"
         "beq         4f\n"
         "convert_macroblock 4\n"
         "4:\n"
         "tst         %[n], #2\n"
         "beq         5f\n"
         "convert_macroblock 2\n"
         "5:\n"
         ".purgem convert_macroblock\n":[src] "+&r" (src),[dst] "+&r" (dst), [n] "+&r" (n) :[acc_r] "r" (&acc_r[0]),[acc_g] "r" (&acc_g[0]),[acc_b] "r" (&acc_b[0])
         :"cc", "memory", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "d11", "d12", "d13", "d14", "d15",
         "d16", "d17", "d18", "d19", "d20", "d21", "d22", "d23",
         "d24", "d25", "d26", "d27", "d28", "d29", "d30", "d31");
}
#endif

class BarcodeVideoProcessorPrivate
{
public:
    int processTimerId;
    int processInterval;
    int enabled;

    QImage               currentFrame;
    zbar::QZBarThread   *readerThread;
    BarcodeViewport     *viewport;
};

BarcodeVideoProcessor::BarcodeVideoProcessor(QObject *parent)
    : QAbstractVideoSurface(parent), d(new BarcodeVideoProcessorPrivate)
{
    TRACE
    d->processTimerId = -1;
    d->processInterval = 750;
    d->viewport = NULL;
    d->enabled = true;

    d->readerThread = new zbar::QZBarThread;
    d->readerThread->start();

    this->setNativeResolution(QSize(640, 480));

    QObject::connect(d->readerThread, SIGNAL(decodedText(QString)), this, SIGNAL(decode(QString)));
    QObject::connect(d->readerThread, SIGNAL(decoded(int,QString)), this, SLOT(onDecoded(int,QString)));
}

BarcodeVideoProcessor::~BarcodeVideoProcessor()
{
    TRACE
    if(d->readerThread) d->readerThread->quit();
    delete this->d;
}

BarcodeViewport* BarcodeVideoProcessor::viewport() const
{
    TRACE
    return d->viewport;
}

void BarcodeVideoProcessor::setViewport(BarcodeViewport *viewport)
{
    TRACE
    d->viewport = viewport;
    emit this->viewportChanged();
}

int BarcodeVideoProcessor::processInterval() const
{
    TRACE
    return d->processInterval;
}

bool BarcodeVideoProcessor::enabled() const
{
    return d->enabled;
}

void BarcodeVideoProcessor::setEnabled(bool enabled)
{
    d->enabled = enabled;
    emit enabledChanged();
}

void BarcodeVideoProcessor::onDecoded(int type, const QString &data)
{
    if (enabled()) {
        DEBUGX << "decoded - type: " << type << " data: " << data;
        emit decode(type, data);
    }
    setEnabled(false);
}

void BarcodeVideoProcessor::setProcessInterval(int interval)
{
    TRACE
    d->processInterval = interval;

    if(d->processTimerId != -1)
    {
        this->killTimer(d->processTimerId);
        d->processTimerId = this->startTimer(d->processInterval);
    }

    emit this->processIntervalChanged(interval);
}

QList<QVideoFrame::PixelFormat> BarcodeVideoProcessor::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    TRACE

    if(handleType == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_UYVY;
    }

    return QList<QVideoFrame::PixelFormat>();
}

bool BarcodeVideoProcessor::start(const QVideoSurfaceFormat &format)
{
    TRACE

    if(d->processTimerId == -1)
    {
        d->processTimerId = this->startTimer(d->processInterval);
    }

    return QAbstractVideoSurface::start(format);
}

void BarcodeVideoProcessor::stop()
{
    TRACE
    d->currentFrame = QImage();

    if(d->processTimerId != -1)
    {
        this->killTimer(d->processTimerId);
        d->processTimerId = -1;
    }

    QAbstractVideoSurface::stop();
}

bool BarcodeVideoProcessor::present(const QVideoFrame &pFrame)
{
    if (!d->enabled) {      // TODO: Temp only, implement a mechanism to
        return false;       // make possible to retrieve the image from which
    }                       // the barcode was extracted successfully.
                            // This "pauses" the viewFinder.

    //TRACE
    QVideoFrame frame = pFrame;

#ifdef __ARM_NEON__
    if(frame.map(QAbstractVideoBuffer::ReadOnly))
    {
        if (frame.pixelFormat() == QVideoFrame::Format_UYVY)
        {
            QImage image(frame.size(), QImage::Format_RGB16);

            const uchar *src = frame.bits();
            uchar *dst = image.bits();

            const int srcLineStep = frame.bytesPerLine();
            const int dstLineStep = frame.bytesPerLine();
            const int h = frame.height();
            const int w = frame.width();

            for (int y=0; y<h; y++)
            {
                uyvy422_to_rgb16_line_neon(dst, src, w);

                src += srcLineStep;
                dst += dstLineStep;
            }

            d->currentFrame = image;
        }
    }
#endif

    if(d->viewport)
    {
        d->viewport->present(d->currentFrame);
    }

    return true;
}

int BarcodeVideoProcessor::set_config (const QString& cfgstr)
{
    TRACE
    return d->readerThread->set_config(cfgstr.toStdString());
}

void BarcodeVideoProcessor::timerEvent(QTimerEvent *event)
{
    TRACE

    if (!d->enabled)
        return;

    if(event->timerId() == d->processTimerId && !d->currentFrame.isNull())
            d->readerThread->pushEvent(new zbar::QZBarThread::ScanImageEvent(d->currentFrame.convertToFormat(QImage::Format_RGB32)));
}
