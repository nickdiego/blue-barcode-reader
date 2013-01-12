import QtQuick 1.1

Item {
    id: button

    signal clicked()

    property url normalImage: ""
    property url activeImage: ""
    property bool isCheckable: false
    property bool pressed: false

    width: buttonImage.width
    height: buttonImage.height

    Image {
        id: buttonImage

        anchors.centerIn: parent

        source: button.normalImage
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            if (button.isCheckable) {
                if (button.pressed)
                    buttonImage.source = button.normalImage;
                else
                    buttonImage.source = button.activeImage;

                button.pressed = !button.pressed;
            }

           button.clicked();
        }
    }
}
