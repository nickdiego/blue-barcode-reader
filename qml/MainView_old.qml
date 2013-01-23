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

    /*Button {
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
    }*/

    CustomCamera {
        id: camera

        /*anchors {
            top: buttonQuit.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }*/
        anchors.fill: parent

        Connections {
            target: camera
            onCodeFound: {
                console.log("QML Code Found: " + code);
                codeText.text = "code: " + code;
                resultDialog.visible = true;
                camera.codeCheck = false;
            }
        }
    }

    Rectangle {
        id: resultDialog
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        visible: false

        Text {
            id: codeText
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 20
            text: "Empty code."
        }

        MouseArea {
            anchors.fill: parent
            enabled: resultDialog.visible
            onClicked: {
                camera.codeCheck = true;
                resultDialog.visible = false;
                codeText.text = "Empty code.";
            }
        }
    }

    MouseArea {
        anchors.fill: camera
        enabled: !resultDialog.visible
        onClicked: {
            if (camera.isActive())
                camera.stop();
            else
                camera.start();
        }
    }
}
