import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    id: window

    property int baseHeight: 35
    property int baseWidth: 480
    property int maxHeight: 400

    width: baseWidth
    height: baseHeight
    y: 0
    x: Screen.width/2 - width/2
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    Rectangle {
        id: anchorContainer

        width: 12
        color: "gray"
        height: baseHeight
        anchors {
            right: parent.right
            top: parent.top
        }
        Column {
            id: dotsColumn

            spacing: 5
            anchors.centerIn: parent
            Rectangle {
                color: "white"
                height: 3
                width: 3
            }
            Rectangle {
                color: "white"
                height: 3
                width: 3
            }
            Rectangle {
                color: "white"
                height: 3
                width: 3
            }
        }
        MouseArea {
            id: dragArea

            property real startx: 0;
            property real starty: 0;

            anchors.fill: parent
            onPressed: {
                startx = mouse.x
                starty = mouse.y
            }
            onPositionChanged: {
                if (window.x+mouse.x-startx >= 0 && window.x+window.width+mouse.x-startx <= Screen.width) {
                    window.x += mouse.x - startx
                }
                if (window.y+mouse.y-starty >= 0 && window.y+height+mouse.y-starty <= Screen.height) {
                    window.y += mouse.y - starty
                }
            }
        }
    }

    Button {
        id: dropdownButton

        anchors {
            right: anchorContainer.left
            top: parent.top
        }
        width: baseHeight
        height: baseHeight
        checkable: true
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                gradient: Gradient {
                    GradientStop { position: 0 ; color: (control.pressed || control.checked) ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: (control.pressed || control.checked) ? "#aaa" : "#ccc" }
                }
            }
        }

        onCheckedChanged: checked ? state="toggled" : state="normal"
        state: "normal"
        states: [
            State {
                name: "normal"
                PropertyChanges {
                    target: window
                    height: baseHeight
                }
                PropertyChanges {
                    target: dropdownButton
                    text: "V"
                }
            },
            State {
                name: "toggled"
                PropertyChanges {
                    target: window
                    height: maxHeight
                }
                PropertyChanges {
                    target: dropdownButton
                    text: "^"
                }
            }
        ]
    }
    Button {
        id: startStopButton

        anchors {
            right: dropdownButton.left
            top: parent.top
        }
        width: 60
        height: baseHeight
        checkable: true
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                gradient: Gradient {
                    GradientStop { position: 0 ; color: (control.pressed || control.checked) ? "red" : "green" }
                    GradientStop { position: 1 ; color: (control.pressed || control.checked) ? "red" : "green" }
                }
            }
        }
        state: "stopped"
        states: [
            State {
                name: "started"
                PropertyChanges {
                    target: dropdownButton
                    text: "STOP"
                }
                when: checked
            },
            State {
                name: "stopped"
                PropertyChanges {
                    target: dropdownButton
                    text: "START"
                }
                when: !checked
            }
        ]
    }
    Rectangle {
        id: timerContainer

        height: window.baseHeight
        width: 80
        color: "#999"
        anchors {
            left: parent.left
            top: parent.top
        }
    }
    TextInput {
        id: taskInput

        anchors {
            top: parent.top
            right: startStopButton.left
            left: timerContainer.right
        }
        height: window.baseHeight
    }
}
