#include "myvideosurface.h"
#include "frameobserver.h"

MyVideoSurface::MyVideoSurface(FrameObserver *target, QObject *parent)
    : QAbstractVideoSurface(parent)
    , m_target(target)
{
    setError(QAbstractVideoSurface::NoError);
}

MyVideoSurface::~MyVideoSurface()
{
}

QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(
    QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_UYVY;
    }

    return QList<QVideoFrame::PixelFormat>();
}

bool MyVideoSurface::start(const QVideoSurfaceFormat &format)
{
    QImage::Format imageFormat =
        QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());

    if (imageFormat == QImage::Format_Invalid)
        imageFormat = QImage::Format_RGB32;

    const QSize frameSize = format.frameSize();

    if ((imageFormat != QImage::Format_Invalid) && !frameSize.isEmpty()) {
        QAbstractVideoSurface::start(format);

        emit frameSizeChanged(frameSize);

        return true;
    }

    return false;
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    return m_target->updateItem(frame);
}
