import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

Item {
    id: root

    property var mission

    signal expand()

    implicitWidth: row.implicitWidth
    implicitHeight: Controls.Theme.baseSize

    Rectangle {
        id: hover
        anchors.fill: parent
        opacity: 0.20
        color: mouseArea.containsMouse ? Controls.Theme.colors.highlight : "transparent"
        radius: Controls.Theme.rounding
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: expand()
    }

    RowLayout {
        id: row
        anchors.fill: parent
        anchors.margins: Controls.Theme.padding
        spacing: Controls.Theme.spacing

        Controls.Label {
            text: mission ? mission.name : ""
            Layout.fillHeight: true
        }

        Controls.Label {
            text: mission ? mission.vehicle : ""
            type: Controls.Theme.Label
            Layout.fillHeight: true
        }

        Item { Layout.fillWidth: true }

        Controls.ColoredIcon {
            implicitWidth: height
            source: "qrc:/icons/right.svg"
            Layout.fillHeight: true
        }
    }
}
