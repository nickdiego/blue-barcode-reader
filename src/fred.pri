SRCDIR = fred

HEADERS += \
    $$SRCDIR/reader/codereaderthread.h \
    $$SRCDIR/reader/codereader.h \
    $$SRCDIR/camera/frameobserver.h \
    $$SRCDIR/camera/yuv2rgb.h \
    $$SRCDIR/camera/myvideosurface.h \
    $$SRCDIR/camera/customcamera.h

SOURCES += \
    $$SRCDIR/reader/codereaderthread.cpp \
    $$SRCDIR/reader/codereader.cpp \
    $$SRCDIR/camera/yuv2rgb.cpp \
    $$SRCDIR/camera/myvideosurface.cpp \
    $$SRCDIR/camera/customcamera.cpp

INCLUDEPATH += \
    $$SRCDIR/reader \
    $$SRCDIR/camera
