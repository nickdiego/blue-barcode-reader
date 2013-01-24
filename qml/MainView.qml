import QtQuick 1.0
import rubyx.BarcodeReader 1.0
import BlueCodeReader 1.0

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

        onEnabledChanged: console.log("reader enabled: " + reader.enabled);
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
        color: Qt.rgba(0, 0, 0, 0.8)
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

    Rectangle {
        id: topBar
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 40
        color: Qt.rgba(0, 0, 0, 0.8)
        z: 98

        property int vMargin: 3
        property int hMargin: 5
        property int textSize: 22

        Text {
            id: statusText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: topBar.hMargin
            anchors.topMargin: topBar.vMargin

            font.pixelSize: topBar.textSize
            color: "white"
            text: "scanning..."
        }

        Text {
            id: bluetoothText
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: topBar.hMargin
            anchors.topMargin: topBar.vMargin

            font.pixelSize: topBar.textSize
            color: {
                if (hidServer.state === HIDServer.CONNECTED) {
                    return "white";
                } else {
                    return "red";
                }
            }

            text: {
                if (hidServer.state === HIDServer.CONNECTED) {
                    return "connected";
                } if (hidServer.state === HIDServer.LISTENING) {
                    return "disconnected";
                } else {
                    return "stopped";
                }
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
            name: "standby"
            PropertyChanges { target: reader; enabled: false }
            PropertyChanges { target: topBar; visible: false }
            PropertyChanges { target: dialog; visible: true }
            PropertyChanges { target: indicator; text: "Stand by" }
        },
        State {
            name: "decoded"
            PropertyChanges { target: reader; enabled: false }
            PropertyChanges { target: topBar; visible: false }
            PropertyChanges { target: dialog; visible: true }
            PropertyChanges { target: indicator; text: main.decoded }
        },
        State {
            name: "reading"
            PropertyChanges { target: topBar; visible: true }
            PropertyChanges { target: dialog; visible: false }
            PropertyChanges { target: reader; enabled: true }
        }
    ]
}
