#####
# linking against "libbluetoothhid" (qt-bluehid-service), dynamically

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/qt-bluehid-service/release/ -lbluetoothhid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/qt-bluehid-service/debug/ -lbluetoothhid
else:symbian: LIBS += -lbluetoothhid
else:unix: LIBS += -L$$OUT_PWD/../libs/qt-bluehid-service -lbluetoothhid

INCLUDEPATH += $$PWD/../libs/qt-bluehid-service/src
DEPENDPATH += $$PWD/../libs/qt-bluehid-service/src

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/qt-bluehid-service/release/bluetoothhid.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/qt-bluehid-service/debug/bluetoothhid.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../libs/qt-bluehid-service/libbluetoothhid.so

contains(MEEGO_EDITION, harmattan) {

    qtbluehidlib.files = \
        $$OUT_PWD/../libs/qt-bluehid-service/libbluetoothhid.so      \
        $$OUT_PWD/../libs/qt-bluehid-service/libbluetoothhid.so.1    \
        $$OUT_PWD/../libs/qt-bluehid-service/libbluetoothhid.so.1.0  \
        $$OUT_PWD/../libs/qt-bluehid-service/libbluetoothhid.so.1.0.0
    qtbluehidlib.path = /opt/$${TARGET}/lib

    QMAKE_LFLAGS += -Wl,--rpath=/opt/$${TARGET}/lib

    INSTALLS += qtbluehidlib
}

#####
# linking against "libdeclarativezbar" - statically
OUT_DZBAR = $$OUT_PWD/../libs/declarative-zbar
PWD_DZBAR = $$PWD/../libs/declarative-zbar

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_DZBAR/release/ -ldeclarativezbar
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_DZBAR/debug/ -ldeclarativezbar
else:symbian: LIBS += -ldeclarativezbar
else:unix: LIBS += -L$$OUT_DZBAR -ldeclarativezbar

INCLUDEPATH += $$PWD_DZBAR/src
DEPENDPATH += $$PWD_DZBAR/src

#contains(MEEGO_EDITION, harmattan) {

#    declarativezbar.files = \
#        $$OUT_DZBAR/libdeclarativezbar.so      \
#        $$OUT_DZBAR/libdeclarativezbar.so.1    \
#        $$OUT_DZBAR/libdeclarativezbar.so.1.0  \
#        $$OUT_DZBAR/libdeclarativezbar.so.1.0.0
#    declarativezbar.path = /opt/$${TARGET}/lib

#    QMAKE_LFLAGS += -Wl,--rpath=/opt/$${TARGET}/lib

#    INSTALLS += declarativezbar
#}

######
# linking against "libzbar" - statically
OUT_ZBAR = $$OUT_PWD/../libs/zbar
PWD_ZBAR = $$PWD/../libs/zbar

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_ZBAR/release/ -lzbar
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_ZBAR/debug/ -lzbar
else:symbian: LIBS += -lzbar
else:unix: LIBS += -L$$OUT_ZBAR -lzbar

LIBS += -ljpeg

#INCLUDEPATH += $$PWD_ZBAR/src
#DEPENDPATH += $$PWD_ZBAR/src

# Any lib else?
# ...
