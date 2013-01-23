/*
 * barcodevideoprocessor.h
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
#ifndef BARCODEVIDEOPROCESSOR_H
#define BARCODEVIDEOPROCESSOR_H

#include "barcodeviewport.h"
#include <QAbstractVideoSurface>

class BarcodeVideoProcessorPrivate;
class BarcodeReader;

class BarcodeVideoProcessor : public QAbstractVideoSurface
{
    Q_OBJECT

    Q_PROPERTY(BarcodeViewport *viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(int processInterval READ processInterval WRITE setProcessInterval NOTIFY processIntervalChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit BarcodeVideoProcessor(QObject *parent = 0);
            ~BarcodeVideoProcessor();

    BarcodeViewport* viewport() const;
    void setViewport(BarcodeViewport *viewport);

    int processInterval() const;
    void setProcessInterval(int interval);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool start(const QVideoSurfaceFormat &format);
    void stop();

    bool present(const QVideoFrame&);

    bool enabled() const;
    void setEnabled(bool enabled);

public Q_SLOTS:
    /// set config parsed from configuration string.
    /// @see zbar_image_scanner_parse_config()
    /// @since 0.4
    int set_config (const QString& cfgstr);

    void onDecoded(int type, const QString &data);

Q_SIGNALS:
    void viewportChanged();
    void processIntervalChanged(int interval);
    void enabledChanged();

    void decode(const QString &data);
    void decode(int type, const QString &data);

protected:
    void timerEvent(QTimerEvent *);

private:
    BarcodeVideoProcessorPrivate *d;
};

#endif // BARCODEVIDEOPROCESSOR_H
