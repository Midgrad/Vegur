import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

RowLayout {
    id: root

    property var mission

    spacing: 0

    Controls.Label {
        text: mission ? mission.name : ""
        Layout.fillWidth: true
    }
}
