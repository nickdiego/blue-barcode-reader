#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T17:01:13
#
#-------------------------------------------------

QT       += core

TARGET = zbar
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += include include/zbar zbar

SOURCES += zbar/config.c \
        zbar/error.c zbar/symbol.c \
        zbar/image.c zbar/convert.c zbar/processor.c \
        zbar/processor/lock.c zbar/refcnt.c\
        zbar/window.c zbar/video.c \
        zbar/img_scanner.c zbar/scanner.c \
        zbar/decoder.c \
        zbar/decoder/ean.c \
        zbar/decoder/code128.c \
        zbar/decoder/code39.c \
        zbar/decoder/i25.c \
        zbar/decoder/qr_finder.c \
        zbar/qrcode/qrdec.c zbar/qrcode/qrdectxt.c \
        zbar/qrcode/rs.c \
        zbar/qrcode/isaac.c \
        zbar/qrcode/bch15_5.c \
        zbar/qrcode/binarize.c \
        zbar/qrcode/util.c \
        zbar/processor/posix.c \
        zbar/video/null.c \
        zbar/jpeg.c \
        zbar/processor/x.c \
        zbar/window/wx.c zbar/window/ximage.c \
        qt/QZBar.cpp qt/QZBarThread.cpp
#       zbar/window/x.c zbar/window/ximage.c

HEADERS += config.h zbar/debug.h \
        zbar/debug.h zbar/error.h \
        zbar/symbol.h zbar/image.h \
        zbar/processor.h \
        zbar/refcnt.h zbar/timer.h \
        zbar/mutex.h zbar/event.h zbar/thread.h zbar/window.h zbar/decoder.h \
        zbar/video.h  zbar/img_scanner.h \
        zbar/decoder/ean.h \
        zbar/decoder/code128.h \
        zbar/decoder/code39.h \
        zbar/decoder/i25.h \
        zbar/qrcode.h \
        zbar/decoder/qr_finder.h \
        zbar/qrcode/qrdec.h \
        zbar/qrcode/rs.h \
        zbar/qrcode/isaac.h \
        zbar/qrcode/bch15_5.h \
        zbar/qrcode/binarize.h \
        zbar/qrcode/util.h \
        zbar/processor/posix.h \
        zbar/window/x.h \
        include/zbar.h \
        include/zbar/Scanner.h include/zbar/Decoder.h \
        include/zbar/Exception.h include/zbar/Symbol.h \
        include/zbar/Image.h include/zbar/ImageScanner.h \
        include/zbar/Video.h include/zbar/Window.h \
        include/zbar/Processor.h \
        include/zbar/QZBar.h include/zbar/QZBarImage.h qt/QZBarThread.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE111FF53
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = zbar-lib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
#    INSTALLS += target
}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
