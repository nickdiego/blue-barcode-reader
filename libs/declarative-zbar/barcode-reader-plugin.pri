QT          += core gui declarative
CONFIG      += qt thread mobility
MOBILITY    += multimedia

#LIBS += -L../../zbar-lib -lzbar
#DEFINES     += WANT_DEBUG

INCLUDEPATH +=  $$PWD/src \
    $$PWD/../../zbar-lib/include \
    $$PWD/../../zbar-lib/include/zbar \
    $$PWD/../../zbar-lib/qt

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
