import QtQuick 1.0
import BlueCodeReader 1.0
import "../constants.js" as Constants

Rectangle {
    id: topBar
    anchors.top: parent.top // TODO default size/positioning
    anchors.left: parent.left
    width: parent.width
    height: 40
    color: Qt.rgba(0, 0, 0, 0.8)
    z: 98

    property Item codeReaderView
    property int vMargin: 3
    property int hMargin: 5
    property int textPixelSize: 22

    state: Constants.ReaderState.IDLE

    Text {
        id: statusText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: topBar.hMargin
        anchors.topMargin: topBar.vMargin

        font.pixelSize: topBar.textPixelSize
        color: "white"

        text: {
            if (codeReaderView.state === Constants.ReaderState.READING)
                return "scanning";
            else
                return "";
        }
    }

    Text {
        id: bluetoothText
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: topBar.hMargin
        anchors.topMargin: topBar.vMargin

        font.pixelSize: topBar.textPixelSize
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
