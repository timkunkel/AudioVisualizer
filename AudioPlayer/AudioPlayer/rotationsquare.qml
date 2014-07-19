import QtQuick 2.0

Rectangle {

    id: root

    Rectangle {
        property int d: 100
        id: square
        width: d
        height: d
        x: 0; y: 0
        color: "red"
        NumberAnimation on rotation { from: 0; to: 360; duration: 2000; loops: Animation.Infinite; }

        Behavior on x { SmoothedAnimation { velocity: 200 } }

    }

    Text {
        anchors.centerIn: parent
        text: "Qt Quick running in a widget"
    }

    focus: true

}
