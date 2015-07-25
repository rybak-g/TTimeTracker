import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    width: 480
    height: 44
    y: Screen.height - height
    x: Screen.width/2 - width/2
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    Button {
        id: mainButton

        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        width: 40
        text: "V"
        checkable: true
        onCheckedChanged: checked ? state="toggled" : state="normal"
        state: "normal"
        states: [
            State {
                name: "normal"
                PropertyChanges {
                    target: window
                    height: 44
                }
                PropertyChanges {
                    target: mainButton
                    text: "V"
                }
            },
            State {
                name: "toggled"
                PropertyChanges {
                    target: window
                    height: 100
                }
                PropertyChanges {
                    target: mainButton
                    text: "^"
                }
            }
        ]
    }
}
