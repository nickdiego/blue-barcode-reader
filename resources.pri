RESOURCES += \
    $$PWD/qml/qml.qrc \
    $$PWD/images/images.qrc

OTHER_FILES += \
    $$PWD/qml/MainView.qml \
    $$PWD/qml/widgets/Button.qml

symbian: {
    RESOURCES += \
        $$PWD/qml/symbian/symbian.qrc

    OTHER_FILES += \
        $$PWD/qml/symbian/symbian.qml
}

contains(MEEGO_EDITION, harmattan) {

    RESOURCES += \
        $$PWD/qml/meego/meego.qrc

    OTHER_FILES += \
        $$PWD/qml/meego/meego.qml
}
