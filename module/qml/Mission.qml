import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

Rectangle {
    id: root

    property var mission

    signal expand()
    property bool hovered: mouseArea.containsMouse

    implicitHeight: Controls.Theme.baseSize
    color: hovered ? Controls.Theme.colors.hover : "transparent"
    radius: Controls.Theme.rounding

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: expand()
    }

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: Controls.Theme.spacing

        Controls.Label {
            text: mission ? mission.name : ""
            Layout.leftMargin: Controls.Theme.margins
        }

        Controls.Label {
            text: mission ? mission.vehicle : ""
            type: Controls.Theme.Label
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.ColoredIcon {
            implicitWidth: Controls.Theme.iconSize
            implicitHeight: width
            source: "qrc:/icons/right.svg"
        }
    }
}
