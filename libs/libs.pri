## TODO: This approach should work!
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/qt-bluehid-service/release/ -lbluetoothhid
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/qt-bluehid-service/debug/ -lbluetoothhid
#else:symbian: LIBS += -lbluetoothhid
#else:unix: LIBS += -L$$OUT_PWD/qt-bluehid-service -lbluetoothhid
#INCLUDEPATH += $$PWD/qt-bluehid-service
#DEPENDPATH += $$PWD/qt-bluehid-service
#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/qt-bluehid-service/release/bluetoothhid.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/qt-bluehid-service/debug/bluetoothhid.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/qt-bluehid-service/libbluetoothhid.a

# Fallback to approach above
include ($$PWD/qt-bluehid-service/qt-bluehid-service.pri)
