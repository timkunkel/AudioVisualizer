import QtQuick 2.0
import QtQuick.Particles 2.0

Rectangle {

    id: root

    Rectangle {
        property int d: 100
        id: square
        width: d
        height: d
        anchors.centerIn: parent
        color: "red"
        NumberAnimation on rotation { from: 0; to: 360; duration: 2000; loops: Animation.Infinite; }
    }

    Text {
        anchors.centerIn: parent
        text: "Qt Quick running in a widget"
    }

    ParticleSystem {
                id: sys
            }

            Emitter {
                anchors.fill: parent
                system: sys
                ImageParticle {
                    anchors.fill: parent
                    system: sys
                    source: "green_melon_blob.png"
                    clip: true
                    id:  redblip
                }

                lifeSpan: 6000
            }
}
