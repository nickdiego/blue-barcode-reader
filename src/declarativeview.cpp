#include <QtDeclarative>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>

#include "declarativeview.h"
#include "customcamera.h"

DeclarativeView::DeclarativeView(QWidget *parent)
    : QDeclarativeView(parent)
{
    registerTypes();

#if defined(Q_OS_SYMBIAN)
    connect(&m_settings, SIGNAL(orientationChanged()),
            SLOT(changeOrientation()), Qt::DirectConnection);
#endif

    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

#if defined(Q_OS_SYMBIAN)
    setSource(QUrl("qrc:/symbian.qml"));
#elif defined(Q_OS_HARMATTAN)
    setSource(QUrl("qrc:/meego.qml"));
#else
    setSource(QUrl("qrc:/MainView.qml"));
#endif

    connect((QObject *) engine(), SIGNAL(quit()), qApp, SLOT(quit()));
}

void DeclarativeView::load()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_OS_HARMATTAN)
    setGeometry(QApplication::desktop()->screenGeometry());
    showFullScreen();
#else
    setGeometry(0, 0, 480, 800);
    show();
#endif
}

#if defined(Q_OS_SYMBIAN)
void DeclarativeView::changeOrientation()
{
    if (m_settings.orientation() == Settings::LandscapeOrientation)
        setAttribute(Qt::WA_LockLandscapeOrientation, true);
    else if (m_settings.orientation() == Settings::PortraitOrientation)
        setAttribute(Qt::WA_LockPortraitOrientation, true);
    else
        setAttribute(Qt::WA_AutoOrientation, true);
}
#endif

void DeclarativeView::registerTypes()
{
    rootContext()->setContextProperty("settings", &m_settings);

    qmlRegisterType<CustomCamera>("Widgets", 1, 0, "CustomCamera");
}
