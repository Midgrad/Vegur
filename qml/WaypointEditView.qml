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

        Controls.CoordSpinBox {
            labelText: qsTr("Latitude")
            visible: waypoint.params.latitude !== undefined
            value: visible ? waypoint.params.latitude : 0
        }

        Controls.CoordSpinBox {
            labelText: qsTr("Longitude")
            isLongitude: true
            visible: waypoint.params.longitude !== undefined
            value: visible ? waypoint.params.longitude : 0
        }

        Controls.RealSpinBox {
            id: altitudeBox
            labelText: qsTr("Altitude")
            realFrom: -500
            realTo: 9999
            visible: waypoint.params.altitude !== undefined
            Binding on realValue { value: waypoint.params.altitude; when: !altitudeBox.activeFocus  && altitudeBox.visible }
        }

        Controls.CheckBox {
            text: qsTr("Relative")
            visible: waypoint.params.relative !== undefined
            checked: visible && waypoint.params.relative
        }
    }
}
