ZBAR_DIR = ../libs/zbar

INCLUDEPATH += $$ZBAR_DIR \
        $$ZBAR_DIR/include \
        $$ZBAR_DIR/include/zbar \
        $$ZBAR_DIR/zbar

LIBS += -ljpeg

SOURCES += $$ZBAR_DIR/zbar/config.c \
        $$ZBAR_DIR/zbar/error.c \
        $$ZBAR_DIR/zbar/symbol.c \
        $$ZBAR_DIR/zbar/image.c \
        $$ZBAR_DIR/zbar/convert.c \
        $$ZBAR_DIR/zbar/processor.c \
        $$ZBAR_DIR/zbar/processor/lock.c \
        $$ZBAR_DIR/zbar/refcnt.c \
        $$ZBAR_DIR/zbar/window.c \
        $$ZBAR_DIR/zbar/video.c \
        $$ZBAR_DIR/zbar/img_scanner.c \
        $$ZBAR_DIR/zbar/scanner.c \
        $$ZBAR_DIR/zbar/decoder.c \
        $$ZBAR_DIR/zbar/decoder/ean.c \
        $$ZBAR_DIR/zbar/decoder/code128.c \
        $$ZBAR_DIR/zbar/decoder/code39.c \
        $$ZBAR_DIR/zbar/decoder/i25.c \
        $$ZBAR_DIR/zbar/decoder/qr_finder.c \
        $$ZBAR_DIR/zbar/qrcode/qrdec.c \
        $$ZBAR_DIR/zbar/qrcode/qrdectxt.c \
        $$ZBAR_DIR/zbar/qrcode/rs.c \
        $$ZBAR_DIR/zbar/qrcode/isaac.c \
        $$ZBAR_DIR/zbar/qrcode/bch15_5.c \
        $$ZBAR_DIR/zbar/qrcode/binarize.c \
        $$ZBAR_DIR/zbar/qrcode/util.c \
        $$ZBAR_DIR/zbar/processor/posix.c \
        $$ZBAR_DIR/zbar/video/null.c \
        $$ZBAR_DIR/zbar/jpeg.c \
        $$ZBAR_DIR/zbar/processor/x.c \
        $$ZBAR_DIR/zbar/window/wx.c \
        $$ZBAR_DIR/zbar/window/ximage.c \
        $$ZBAR_DIR/qt/QZBar.cpp \
        $$ZBAR_DIR/qt/QZBarThread.cpp
#       zbar/window/x.c zbar/window/ximage.c

HEADERS += $$ZBAR_DIR/config.h \
        $$ZBAR_DIR/zbar/debug.h \
        $$ZBAR_DIR/zbar/debug.h zbar/error.h \
        $$ZBAR_DIR/zbar/symbol.h zbar/image.h \
        $$ZBAR_DIR/zbar/processor.h \
        $$ZBAR_DIR/zbar/refcnt.h \
        $$ZBAR_DIR/zbar/timer.h \
        $$ZBAR_DIR/zbar/mutex.h \
        $$ZBAR_DIR/zbar/event.h \
        $$ZBAR_DIR/zbar/thread.h \
        $$ZBAR_DIR/zbar/window.h \
        $$ZBAR_DIR/zbar/decoder.h \
        $$ZBAR_DIR/zbar/video.h \
        $$ZBAR_DIR/zbar/img_scanner.h \
        $$ZBAR_DIR/zbar/decoder/ean.h \
        $$ZBAR_DIR/zbar/decoder/code128.h \
        $$ZBAR_DIR/zbar/decoder/code39.h \
        $$ZBAR_DIR/zbar/decoder/i25.h \
        $$ZBAR_DIR/zbar/qrcode.h \
        $$ZBAR_DIR/zbar/decoder/qr_finder.h \
        $$ZBAR_DIR/zbar/qrcode/qrdec.h \
        $$ZBAR_DIR/zbar/qrcode/rs.h \
        $$ZBAR_DIR/zbar/qrcode/isaac.h \
        $$ZBAR_DIR/zbar/qrcode/bch15_5.h \
        $$ZBAR_DIR/zbar/qrcode/binarize.h \
        $$ZBAR_DIR/zbar/qrcode/util.h \
        $$ZBAR_DIR/zbar/processor/posix.h \
        $$ZBAR_DIR/zbar/window/x.h \
        $$ZBAR_DIR/include/zbar.h \
        $$ZBAR_DIR/include/zbar/Scanner.h \
        $$ZBAR_DIR/include/zbar/Decoder.h \
        $$ZBAR_DIR/include/zbar/Exception.h \
        $$ZBAR_DIR/include/zbar/Symbol.h \
        $$ZBAR_DIR/include/zbar/Image.h \
        $$ZBAR_DIR/include/zbar/ImageScanner.h \
        $$ZBAR_DIR/include/zbar/Video.h \
        $$ZBAR_DIR/include/zbar/Window.h \
        $$ZBAR_DIR/include/zbar/Processor.h \
        $$ZBAR_DIR/include/zbar/QZBar.h \
        $$ZBAR_DIR/include/zbar/QZBarImage.h \
        $$ZBAR_DIR/qt/QZBarThread.h
