# linking against "libbluetoothhid" (qt-bluehid-service)
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


# Any lib else?
# ...
