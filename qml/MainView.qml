import QtQuick 1.0
import ".."
import "widgets"

Item {
    id: root

    TopBar {
        id: topBar

        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 40

        codeReaderView: codeReaderView
    }

    CodeReaderView {
        id: codeReaderView
        anchors.fill: parent
    }
}
