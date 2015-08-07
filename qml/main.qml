import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2
import PluginManager 1.0

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
                color: "#DDDDDD"
                height: 3
                width: 3
                radius: 1
            }
            Rectangle {
                color: "#DDDDDD"
                height: 3
                width: 3
                radius: 1
            }
            Rectangle {
                color: "#DDDDDD"
                height: 3
                width: 3
                radius: 1
            }
        }
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////f
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
            id: dropdownButtonImage

            anchors.centerIn: parent
            height: parent.height*0.5
            width: parent.height*0.5
            sourceSize {
                height: 128
                width: 128
            }
            fillMode: Image.PreserveAspectFit
            source: (dropdownButton.checked || dropdownButton.pressed) ? "qrc:/cog/cog/lnr-cog-444.svg" : "qrc:/cog/cog/lnr-cog-ddd.svg"
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
            rightMargin: -1
            right: dropdownButton.left
            top: parent.top
        }
        width: 60
        height: baseHeight
        checkable: true
        style: ButtonStyle {
            background: Rectangle {
                color: "#444444"
                border {
                    color: "#444444"
                    width: 1
                }
                SequentialAnimation on color {
                    id: animation

                    alwaysRunToEnd: true
                    running: control.checked
                    loops: Animation.Infinite
                    PropertyAnimation { to: "#963821"; easing.type: Easing.OutQuad; duration: 1000 }
                    PropertyAnimation { to: "#444444"; easing.type: Easing.InQuad; duration: 1000 }
                }
            }
        }
        Image {
            id: startStopButtonImage

            anchors.centerIn: parent
            height: parent.height*0.4
            width: parent.height*0.4
            sourceSize {
                height: 128
                width: 128
            }
            source: (startStopButton.checked) ? "qrc:/stop/stop/stop-button-ddd.svg" : "qrc:/play/play/play-button-ddd.svg"
            fillMode: Image.PreserveAspectFit
        }
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
            color: "#DDDDDD"
            text: (parent.hours < 10 ? "0"+parent.hours : parent.hours) + ":" +
                  (parent.minutes < 10 ? "0"+parent.minutes : parent.minutes) + ":" +
                  (parent.seconds < 10 ? "0"+parent.seconds : parent.seconds)
            font.pixelSize: parent.height*0.4
        }
        Text {
            id: daysText
            text: parent.days > 0 ? (((parent.days < 10) ? "00" : (parent.days < 100) ? "0" : "")) + parent.days : ""
            color: "#DDDDDD"
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
            rightMargin: -1
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
            anchors {
                fill: parent
                topMargin: 2
                leftMargin: 10
                rightMargin: 10
            }
            verticalAlignment: Text.AlignVCenter
            color: "#444"
            font {
                pixelSize: parent.height*0.4
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
        }
        function start() {
            running = true;
        }
        function stop() {
            running = false
        }
    }
    PluginManager {
        id: manager

        pluginDirectory: "C:/"
        Component.onCompleted: {
            manager.refreshPluginList();
            manager.loadServiceProvider("Phabricator");
            manager.getTasks();
        }
    }
}
