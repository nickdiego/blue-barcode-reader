#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

class FrameObserver;

class MyVideoSurface: public QAbstractVideoSurface
{
    Q_OBJECT

public:
    MyVideoSurface(FrameObserver *target, QObject *parent = 0);
    ~MyVideoSurface();

    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
                QAbstractVideoBuffer::HandleType handleType =
                    QAbstractVideoBuffer::NoHandle) const;
    virtual bool start(const QVideoSurfaceFormat &format);

    virtual bool present(const QVideoFrame &frame);

signals:
    void frameSizeChanged(const QSize &size);

private:
    FrameObserver *m_target;
};

#endif
