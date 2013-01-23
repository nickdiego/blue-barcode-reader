TEMPLATE     = lib
TARGET       = barcode-reader-plugin

QT           = core gui declarative
CONFIG       = qt thread plugin mobility
MOBILITY    += multimedia

LIBS += -L../../zbar-lib -lzbar
#DEFINES     += WANT_DEBUG

INCLUDEPATH +=  ../../zbar-lib/include ../../zbar-lib/include/zbar ../../zbar-lib/qt

#TODO: Only when building for MeeGo CE
#QMAKE_CXXFLAGS = -mfpu=neon

HEADERS = \
    common.h \
    barcodereaderplugin.h \
    barcodevideoprocessor.h \
    barcodeviewport.h \
    barcodereader.h
#    zbar/QZBarThread.h \
#    zbar/QZBarImage.h \
#    zbar/QZBar.h \

SOURCES = \
    barcodereaderplugin.cpp \
    barcodevideoprocessor.cpp \
    barcodeviewport.cpp \
    barcodereader.cpp
#    zbar/QZBarThread.cpp \
#    zbar/QZBar.cpp \

OTHER_FILES += \
    barcode-reader-plugin.qmldir

#target.path = /usr/lib/qt4/imports/stage/rubyx/BarcodeReader
target.path = /opt/searchfoot/imports/stage/rubyx/BarcodeReader
INSTALLS = target
