import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    id: window

    property int baseHeight: 40
    property int baseWidth: 480
    property int maxHeight: 400

    width: baseWidth
    height: baseHeight
    y: 0
    x: Screen.width/2 - width/2
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    color: "#00BBBBBB"

    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    Rectangle {
        id: anchorContainer

        width: 12
        color: "#444"
        height: baseHeight
        anchors {
            right: parent.right
            top: parent.top
        }
        Column {
            id: dotsColumn

            spacing: 5
            anchors.centerIn: parent
            ///////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////
            //
            ///////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////
            Rectangle {
                color: "#DDD"
                height: 3
                width: 3
                radius: 3
            }
            Rectangle {
                color: "#DDD"
                height: 3
                width: 3
                radius: 3
            }
            Rectangle {
                color: "#DDD"
                height: 3
                width: 3
                radius: 3
            }
        }
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    Button {
        id: dropdownButton

        anchors {
            right: anchorContainer.left
            top: parent.top
            rightMargin: -2
        }
        width: baseHeight
        height: baseHeight
        checkable: true
        style: ButtonStyle {
            background: Rectangle {
                border {
                    width: 1
                    color: "#444"
                }
                gradient: Gradient {
                    GradientStop { position: 0 ; color: (control.pressed || control.checked) ? "#DDD" : "#444" }
                    GradientStop { position: 1 ; color: (control.pressed || control.checked) ? "#DDD" : "#444" }
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
            },
            State {
                name: "toggled"
                PropertyChanges {
                    target: window
                    height: maxHeight
                }
            }
        ]
        Image {
            id: cogImage

            anchors.centerIn: parent
            height: parent.height/2
            width: parent.width/2
            sourceSize {
                height: 512
                width: 512
            }

            source: (dropdownButton.checked || dropdownButton.pressed) ? "qrc:/icon/lnr-cog-444.svg" : "qrc:/icon/lnr-cog-ddd.svg"
        }
    }
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    Rectangle {
        id: timerContainer

        height: window.baseHeight
        width: 80
        color: "#444"
        anchors {
            left: parent.left
            top: parent.top
        }

        property int days;
        property int hours;
        property int minutes;
        property int seconds;
        property int milliseconds;

        Text {
            id: hourMinutesText
            anchors.centerIn: parent
            color: "#DDD"
            text: (parent.hours < 10 ? "0"+parent.hours : parent.hours) + ":" +
                  (parent.minutes < 10 ? "0"+parent.minutes : parent.minutes) + ":" +
                  (parent.seconds < 10 ? "0"+parent.seconds : parent.seconds)
            font.pixelSize: 14
        }
        Text {
            id: daysText
            text: parent.days > 0 ? parent.days : ""
            color: "#DDD"
            font.pixelSize: 10
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottom: hourMinutesText.top
            }
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
//        Text {
//            id: millisecondsText
//            text: parent.milliseconds < 100 ? ((parent.milliseconds < 10 ? "00" : "0")+parent.milliseconds) : parent.milliseconds
//            color: "#DDD"
//            anchors {
//                right: parent.right
//                top: hourMinutesText.bottom
//                left: parent.left
//                bottom: parent.bottom
//            }
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//            font.pixelSize: 10
//        }
    }
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    Rectangle {
        id: taskInputContainer

        anchors {
            top: parent.top
            right: startStopButton.left
            left: timerContainer.right
        }
        border {
            width: 1
            color: "#444"
        }
        clip: true
        color: "transparent"
        height: window.baseHeight
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////
        TextInput {
            id: taskInput
            anchors{
                fill: parent
                topMargin: 2
                leftMargin: 10
                rightMargin: 10
            }
            verticalAlignment: Text.AlignVCenter
            color: "#444"
            font {
                pixelSize: parent.height/2
            }
        }
    }
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    Timer {
        id: timer

        property double time: 0;

        interval: 1000
        repeat: true
        running: startStopButton.checked
        onTriggered: {
            time += interval;
            timerContainer.days = time / (86400000);
            timerContainer.hours = (time / (3600000)) % 24;
            timerContainer.minutes = (time / (60000)) % 60;
            timerContainer.seconds = time / (1000) % 60;
//            timerContainer.milliseconds = time % 1000;
        }
        function start() {
            running = true;
        }
        function stop() {
            running = false
        }
    }
}
