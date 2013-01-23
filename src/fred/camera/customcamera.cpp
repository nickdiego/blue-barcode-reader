#include <QtGui/QPainter>
#include <QVideoRendererControl>

#include <QPen>

#include "customcamera.h"
#include "codereader.h"
#include "myvideosurface.h"

#include <QtDebug>

CustomCamera::CustomCamera(QDeclarativeItem *parent)
    : QDeclarativeItem(parent)
    , m_active(false)
    , m_camera(0)
    , m_myVideoSurface(0)
    , m_targetImage(QImage())
    , m_imageRect(QRect())
    , m_codeCheck(false)
    , m_codeReader(new CodeReader(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);

    initialize();
}

CustomCamera::~CustomCamera()
{
    freeResources();
}

void CustomCamera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());

    QTransform newTransform;
    newTransform = painter->transform();
    newTransform = m_transform * newTransform;
    painter->setTransform(newTransform);

    painter->drawImage(0, 0, m_targetImage);
}

bool CustomCamera::updateItem(const QVideoFrame &frame)
{
    m_frame = frame;

    if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {
        if (m_frame.pixelFormat() == QVideoFrame::Format_UYVY) {
            m_yuv2Rgb.convert(m_frame.bits(), m_frame.width(), m_frame.height());

            m_targetImage = QImage(m_yuv2Rgb.bits(), m_yuv2Rgb.width(),
                                   m_yuv2Rgb.height(), m_yuv2Rgb.width() * 4,
                                   QImage::Format_RGB32);
        } else if (m_frame.pixelFormat() == QVideoFrame::Format_RGB32) {
            m_targetImage = QImage(m_frame.bits(), m_frame.width(),
                                   m_frame.height(), m_frame.bytesPerLine(),
                                   QImage::Format_RGB32);
        } else {
            qDebug("Unhandled format: ARGB32");

            m_targetImage = QImage();
        }

        m_imageRect = m_targetImage.rect();

        update();

        // Check for Barcodes and QR codes
        if (m_codeCheck) {
            if (!m_codeReader->isProcessing())
                m_codeReader->checkForCodes(m_targetImage);
        }

        m_frame.unmap();
    }

    return true;
}

bool CustomCamera::isActive() const
{
    return (m_camera->status() == QCamera::ActiveStatus);
}

void CustomCamera::setCodeCheck(const bool &flag)
{
    if (m_codeCheck != flag) {
        m_codeCheck = flag;

        emit codeCheckChanged();
    }
}

bool CustomCamera::codeCheck() const
{
    return m_codeCheck;
}

void CustomCamera::start()
{
    if (m_camera->status() == QCamera::LoadedStatus) {
        m_camera->start();
    }

    connect(m_codeReader, SIGNAL(codeFound(QString)), this, SIGNAL(codeFound(QString)));
    setCodeCheck(true);
}

void CustomCamera::stop()
{
    if ((m_camera->status() == QCamera::LoadedStatus)
        || (m_camera->status() == QCamera::LoadingStatus)) {
        return;
    }

    if (m_camera->status() == QCamera::ActiveStatus) {
        m_camera->stop();
    }

    setCodeCheck(false);
    disconnect(m_codeReader, SIGNAL(codeFound(QString)), this, SIGNAL(codeFound(QString)));
}

void CustomCamera::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    qDebug() << "geometryChanged: " << newGeometry.width() << "x" << newGeometry.height();
//    if (newGeometry != oldGeometry) {
//        setTransformOriginPoint(newGeometry.width(), 0);

//        m_transform.reset();
//        m_transform.translate(newGeometry.width(), 0);
//        m_transform.rotate(90);
//    }

    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void CustomCamera::cameraStateChanged(QCamera::State state)
{
    qDebug() << "Camera State: " << state;
}

void CustomCamera::handleCameraError(QCamera::Error error)
{
    qDebug() << "Camera Error: " << error << "; "
             << "Camera Error String: " << m_camera->errorString();
}

void CustomCamera::initialize()
{
    freeResources();

    QList<QByteArray> cameraDevices = QCamera::availableDevices();

    // Primary camera is the default one
    m_camera = new QCamera(cameraDevices[0]);

    connect(m_camera, SIGNAL(error(QCamera::Error)),
            this, SLOT(handleCameraError(QCamera::Error)));
    connect(m_camera, SIGNAL(stateChanged(QCamera::State)),
            this, SLOT(cameraStateChanged(QCamera::State)));

    // Make sure the camera is in loaded state
    m_camera->load();

    QMediaService *mediaService = m_camera->service();
    QVideoRendererControl *rendererControl =
            mediaService->requestControl<QVideoRendererControl *>();

    m_myVideoSurface = new MyVideoSurface(this, this);

    rendererControl->setSurface(m_myVideoSurface);
}

void CustomCamera::freeResources()
{
    if (m_myVideoSurface)
        m_myVideoSurface->stop();

    if (m_camera) {
        m_camera->stop();
        m_camera->unload();

        delete m_camera;
        m_camera = 0;
    }
}
