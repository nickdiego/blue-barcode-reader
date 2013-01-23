#ifndef CUSTOMCAMERA_H
#define CUSTOMCAMERA_H

#include <QCamera>
#include <QtDeclarative/QDeclarativeItem>
#include <QtGui/QImage>
#include <QtGui/QTransform>

#include "frameobserver.h"
#include "yuv2rgb.h"

class CodeReader;
class MyVideoSurface;
class QPainter;

class CustomCamera : public QDeclarativeItem, public FrameObserver
{
    Q_OBJECT
    Q_PROPERTY(bool codeCheck READ codeCheck WRITE setCodeCheck NOTIFY codeCheckChanged)

public:
    CustomCamera(QDeclarativeItem *parent = 0);
    ~CustomCamera();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

    virtual bool updateItem(const QVideoFrame &frame);

    Q_INVOKABLE bool isActive() const;

    void setCodeCheck(const bool &flag);
    bool codeCheck() const;

public slots:
    void start();
    void stop();

signals:
    void codeCheckChanged();
    void codeFound(const QString &code);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

protected slots:
    void cameraStateChanged(QCamera::State state);
    void handleCameraError(QCamera::Error error);

private:
    void initialize();
    void freeResources();

    bool m_active;
    QCamera *m_camera;
    MyVideoSurface *m_myVideoSurface;
    QVideoFrame m_frame;
    QImage m_targetImage;
    QRect m_imageRect;
    QTransform m_transform;
    Yuv2Rgb m_yuv2Rgb;
    bool m_codeCheck;
    CodeReader *m_codeReader;
};

#endif
