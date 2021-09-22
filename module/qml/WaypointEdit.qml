import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

ColumnLayout {
    id: root

    property var waypoint

    signal collapse()

    spacing: Controls.Theme.spacing

    Widgets.PropertyTable {
        flat: true
        labelWidth: Controls.Theme.baseSize * 6
        Layout.fillWidth: true

        Controls.TextField {
            id: nameEdit
            labelText: qsTr("Name")
            Binding on text { value: waypoint ? waypoint.name : ""; when: !nameEdit.activeFocus }
        }

        Controls.ComboBox {
            labelText: qsTr("Type")
            displayText: waypoint ? waypoint.type : ""
        }
    }
}
