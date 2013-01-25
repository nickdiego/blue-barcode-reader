QMLDIR = ../qml
IMGDIR = ../images

RESOURCES += \
    $$QMLDIR/qml.qrc \
    $$IMGDIR/images.qrc

OTHER_FILES += \
    $$QMLDIR/CodeReaderView.qml \
    $$QMLDIR/widgets/Button.qml \
    $$QMLDIR//widgets/TopBar.qml \
    $$QMLDIR//MainView.qml \
    $$QMLDIR//constants.js

symbian: {
    RESOURCES += \
        $$QMLDIR/symbian/symbian.qrc

    OTHER_FILES += \
        $$QMLDIR/symbian/symbian.qml
}

contains(MEEGO_EDITION, harmattan) {

    RESOURCES += \
        $$QMLDIR/meego/meego.qrc

    OTHER_FILES += \
        $$QMLDIR/meego/meego.qml
}



