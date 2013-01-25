import QtQuick 1.0
import rubyx.BarcodeReader 1.0
import "constants.js" as Constants

Item {
    id:main
    width:800;height:480

    property string decoded: ""

    Component.onCompleted: {
        //reader.set_config("ean13.config=enable");
        reader.start();
    }

    Component.onDestruction: {
        reader.stop();
    }

    BarcodeReader {
        id:reader
        viewport:viewport

        onDecode: {
            main.decoded = "Type: " + type + "\n" + "Data: " + data;
            main.state = "decoded";
            hidStringSender.send(data);
        }

        //onEnabledChanged: console.log("reader enabled: " + reader.enabled);
    }

    BarcodeViewport {
        id:viewport
        anchors.fill:parent

        MouseArea {
            anchors.fill:parent
            onClicked: main.state = "reading"
        }
    }

    Rectangle {
        id: dialog
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.6)
        z: 99
        visible: false

        Item {
            id: dialogContent
            height: childrenRect.height
            width: childrenRect.width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Image { // TODO
                id: imageWithCode
                width: 0
                height: 0
                visible: false
            }

            Text {
                id:indicator
                anchors.top: parent.top
                anchors.left: parent.left
                font.pixelSize: 30
                color: "white"
                text: ""
            }
        }
    }

    Connections {
        target: appInfo
        onFocusLost: main.state = "standby"
        onFocusGot: main.state = "reading"
    }

    states: [
        State {
            name: Constants.ReaderState.STANDBY
            PropertyChanges { target: reader; enabled: false }
            PropertyChanges { target: dialog; visible: true }
            PropertyChanges { target: indicator; text: "Stand by" }
        },
        State {
            name: Constants.ReaderState.DECODED
            PropertyChanges { target: reader; enabled: false }
            PropertyChanges { target: dialog; visible: true }
            PropertyChanges { target: indicator; text: main.decoded }
        },
        State {
            name: Constants.ReaderState.READING
            PropertyChanges { target: dialog; visible: false }
            PropertyChanges { target: reader; enabled: true }
        }
    ]
}
