import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

// TODO: expandable
Item {
    id: root

    property var waypoint

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
            text: waypoint ? waypoint.name : ""
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: waypoint ? waypoint.type : ""
            type: Controls.Theme.Label
            Layout.fillHeight: true
        }
    }
}
