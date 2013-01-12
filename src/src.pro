TEMPLATE = app
TARGET = bluebarcodereader
QT += gui declarative

include (../resources.pri)

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

## Qt Mobility Multimedia for acessing the camera
CONFIG += mobility
MOBILITY += multimedia

HEADERS += \
    declarativeview.h \
    settings.h \
    reader/codereaderthread.h \
    reader/codereader.h \
    camera/frameobserver.h \
    camera/yuv2rgb.h \
    camera/myvideosurface.h \
    camera/customcamera.h

SOURCES += \
    main.cpp \
    declarativeview.cpp \
    settings.cpp \
    reader/codereaderthread.cpp \
    reader/codereader.cpp \
    camera/yuv2rgb.cpp \
    camera/myvideosurface.cpp \
    camera/customcamera.cpp

INCLUDEPATH += \
    reader \
    camera

## TODO: Uncomment when integrating with bluetooth stuff
## FIXME: When ?? is uncommented, app doesn't start properly, investigate it!?
include(bluetooth.pri)
include(linkage.pri)

TEMP_DIR = $$OUT_PWD/tmp
MOC_DIR = $$TEMP_DIR
OBJECTS_DIR = $$TEMP_DIR
RCC_DIR = $$TEMP_DIR

symbian: {
    TARGET.UID3 = 0xe6b188f7

    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x20000 0x8000000

    TARGET.CAPABILITY += \
        LocalServices \
        ReadUserData \
        WriteUserData \
        UserEnvironment

    QMAKE_DISTCLEAN += $$PWD/.make.cache $$PWD/*.sis $$TEMP_DIR
}

contains(MEEGO_EDITION, harmattan) {

    desktopfile.files = ../qtc_packaging/$${TARGET}_harmattan.desktop
    desktopfile.path = /usr/share/applications

    icon.files = ../qtc_packaging/$${TARGET}80.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktopfile icon

    OTHER_FILES += \
        ../qtc_packaging/debian_harmattan/rules \
        ../qtc_packaging/debian_harmattan/README \
        ../qtc_packaging/debian_harmattan/manifest.aegis \
        ../qtc_packaging/debian_harmattan/copyright \
        ../qtc_packaging/debian_harmattan/control \
        ../qtc_packaging/debian_harmattan/compat \
        ../qtc_packaging/debian_harmattan/changelog

    QMAKE_DISTCLEAN += -r $$TEMP_DIR
}

unix:!symbian {
    QMAKE_DISTCLEAN += -r $$TEMP_DIR
}

contains(MEEGO_EDITION, harmattan) {

    DEFINES += Q_OS_HARMATTAN
    target.path = /opt/$${TARGET}/bin

    INSTALLS += target
}
