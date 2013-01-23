TEMPLATE = lib
CONFIG += staticlib
TARGET = declarativezbar

QT          += core gui declarative
CONFIG      += qt thread mobility
MOBILITY    += multimedia

#LIBS += -LZBAR_DIR -lzbar
#DEFINES     += WANT_DEBUG

ZBAR_DIR = $$PWD/../zbar

INCLUDEPATH +=  $$PWD/src \
    $$ZBAR_DIR/include \
    $$ZBAR_DIR/include/zbar \
    $$ZBAR_DIR/qt

#TODO: Only when building for MeeGo CE
#QMAKE_CXXFLAGS = -mfpu=neon

HEADERS += \
    $$PWD/src/common.h \
    $$PWD/src/barcodevideoprocessor.h \
    $$PWD/src/barcodeviewport.h \
    $$PWD/src/barcodereader.h
#    $$PWD/src/barcodereaderplugin.h \

SOURCES += \
    $$PWD/src/barcodevideoprocessor.cpp \
    $$PWD/src/barcodeviewport.cpp \
    $$PWD/src/barcodereader.cpp
#    $$PWD/src/barcodereaderplugin.cpp \

OTHER_FILES = qml/qmldir
