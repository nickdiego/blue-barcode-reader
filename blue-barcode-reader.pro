TEMPLATE = app

TARGET = bluebarcodereader

QT += core gui declarative

TEMP_DIR = $$OUT_PWD/tmp
MOC_DIR = $$TEMP_DIR
OBJECTS_DIR = $$TEMP_DIR
RCC_DIR = $$TEMP_DIR

## Qt Mobility Multimedia for acessing the camera
CONFIG += mobility
MOBILITY += multimedia

HEADERS += \
    src/declarativeview.h \
    src/settings.h \
    src/reader/codereaderthread.h \
    src/reader/codereader.h \
    src/camera/frameobserver.h \
    src/camera/yuv2rgb.h \
    src/camera/myvideosurface.h \
    src/camera/customcamera.h

SOURCES += \
    src/main.cpp \
    src/declarativeview.cpp \
    src/settings.cpp \
    src/reader/codereaderthread.cpp \
    src/reader/codereader.cpp \
    src/camera/yuv2rgb.cpp \
    src/camera/myvideosurface.cpp \
    src/camera/customcamera.cpp


INCLUDEPATH += \
    src/reader \
    src/camera

RESOURCES += \
    qml/qml.qrc \
    images/images.qrc

OTHER_FILES += \
    qml/MainView.qml \
    qml/widgets/Button.qml

## TODO: Uncomment when integrating with bluetooth stuff
## FIXME: When ?? is uncommented, app doesn't start properly, investigate it!
include(bluetooth.pri)
include(libs/libs.pri)

symbian: {
    TARGET.UID3 = 0xe6b188f7

    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x20000 0x8000000

    TARGET.CAPABILITY += \
        LocalServices \
        ReadUserData \
        WriteUserData \
        UserEnvironment

    RESOURCES += \
        qml/symbian/symbian.qrc

    OTHER_FILES += \
        qml/symbian/symbian.qml

    QMAKE_DISTCLEAN += $$PWD/.make.cache $$PWD/*.sis $$TEMP_DIR
}

contains(MEEGO_EDITION, harmattan) {

    DEFINES += Q_OS_HARMATTAN

    target.path = /opt/$${TARGET}/bin

    desktopfile.files = qtc_packaging/$${TARGET}_harmattan.desktop
    desktopfile.path = /usr/share/applications

    icon.files = qtc_packaging/$${TARGET}80.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktopfile icon target

    RESOURCES += \
        qml/meego/meego.qrc

    OTHER_FILES += \
        qml/meego/meego.qml

    OTHER_FILES += \
        qtc_packaging/debian_harmattan/rules \
        qtc_packaging/debian_harmattan/README \
        qtc_packaging/debian_harmattan/manifest.aegis \
        qtc_packaging/debian_harmattan/copyright \
        qtc_packaging/debian_harmattan/control \
        qtc_packaging/debian_harmattan/compat \
        qtc_packaging/debian_harmattan/changelog

    QMAKE_DISTCLEAN += -r $$TEMP_DIR
}

unix:!symbian {
    QMAKE_DISTCLEAN += -r $$TEMP_DIR
}
