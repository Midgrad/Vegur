import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

Rectangle {
    id: root

    property var mission

    signal expand()
    property bool hovered: mouseArea.containsMouse

    implicitHeight: row.implicitHeight
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
        spacing: 0

        Controls.Label {
            text: mission ? mission.name : ""
            Layout.fillWidth: true
        }
    }
}
