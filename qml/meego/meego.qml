import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: window

    showStatusBar: false
    showToolBar: false

    initialPage: mainPage

    Page {
        id: mainPage

        orientationLock: PageOrientation.LockLandscape
        /*{
            if (settings.orientation == 0)
                PageOrientation.LockLandscape;
            else if (settings.orientation == 1)
                PageOrientation.LockPortrait;
            else
                PageOrientation.Automatic;
        }*/

        MainView {
            id: mainView

            anchors.fill: parent
        }
    }
}
