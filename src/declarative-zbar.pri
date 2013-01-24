QT          += core gui declarative
CONFIG      += qt thread mobility
MOBILITY    += multimedia

#LIBS += -L../../zbar-lib -lzbar
#DEFINES     += WANT_DEBUG

ZBAR_DIR = $$PWD/../libs/zbar
DZBAR_DIR = $$PWD/../libs/declarative-zbar/src

INCLUDEPATH +=  $$DZBAR_DIR \
    $$ZBAR_DIR/include \
    $$ZBAR_DIR/include/zbar \
    $$ZBAR_DIR/qt

#TODO: Only when building for MeeGo CE
#QMAKE_CXXFLAGS = -mfpu=neon

HEADERS += \
    $$DZBAR_DIR/common.h \
    $$DZBAR_DIR/barcodevideoprocessor.h \
    $$DZBAR_DIR/barcodeviewport.h \
    $$DZBAR_DIR/barcodereader.h
#    $$DZBAR_DIR/src/barcodereaderplugin.h \

SOURCES += \
    $$DZBAR_DIR/barcodevideoprocessor.cpp \
    $$DZBAR_DIR/barcodeviewport.cpp \
    $$DZBAR_DIR/barcodereader.cpp
#    $$DZBAR_DIR/src/barcodereaderplugin.cpp \

OTHER_FILES = $$DZBAR_DIR/qml/qmldir
