import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

Item {
    id: root

    property var mission

    signal collapse()

    implicitWidth: grid.implicitWidth
    implicitHeight: grid.implicitHeight

    GridLayout {
        id: grid
        anchors.fill: parent
        rowSpacing: 1
        columnSpacing: 1
        columns: 2

        Controls.Label {
            text: qsTr("Name")
            Layout.fillWidth: true
        }

        Controls.TextField {
            flat: true
            text: mission ? mission.name : ""
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Vehicle")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: vehiclesCombo
            flat: true
            model: controller.vehicles
            Binding on currentIndex {
                value: mission ? controller.vehicles.indexOf(mission.vehicle) : -1
                when: !vehiclesCombo.activeFocus
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Route")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: routesCombo
            flat: true
            model: controller.routes
            Binding on currentIndex {
                value: mission ? controller.routes.indexOf(mission.route) : -1
                when: !routesCombo.activeFocus
            }
            Layout.fillWidth: true
        }
    }
}
