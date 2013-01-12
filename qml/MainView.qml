import QtQuick 1.1
import Widgets 1.0

import "widgets"

Item {
    id: main

    Rectangle {
        id: background

        anchors.fill: parent

        color: "white"
    }

    Button {
        id: buttonQuit

        z: 10

        anchors {
            top: parent.top
            topMargin: parent.height / 50
            right: parent.right
            rightMargin: parent.width / 50
        }

        normalImage: "qrc:/widgets/ButtonQuit.png"

        onClicked: {
            Qt.quit();
        }
    }

    CustomCamera {
        id: camera

        anchors {
            top: buttonQuit.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    MouseArea {
        anchors.fill: camera

        onClicked: {
            if (camera.isActive())
                camera.stop();
            else
                camera.start();
        }
    }
}
