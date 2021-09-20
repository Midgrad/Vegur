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
        rowSpacing: Controls.Theme.spacing
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
            onActivated: controller.assignMission(mission, currentItem)
            Layout.fillWidth: true
        }

//        Controls.Label {
//            text: qsTr("Route")
//            Layout.fillWidth: true
//        }

//        Controls.ComboBox {
//            id: routesCombo
//            flat: true
//            model: controller.routes
//            Binding on currentIndex {
//                value: mission ? controller.routes.indexOf(mission.route) : -1
//                when: !routesCombo.activeFocus
//            }
//            Layout.fillWidth: true
//        }
        Controls.ProgressBar {
            id: progress
            flat: true
            radius: Controls.Theme.rounding
            from: 0
            visible: mission && !mission.complete
            to: mission ? mission.total : 0
            value: mission ? mission.progress : 0
            Layout.fillWidth: true
            Layout.columnSpan: 2

            Controls.Button {
                anchors.fill: parent
                flat: true
                tipText: qsTr("Cancel")
                text: progress.value + "/" + progress.to
                onClicked: mission.cancel()
            }
        }

        Controls.ButtonBar {
            id: bar
            flat: true
            visible: mission && mission.complete
            Layout.fillWidth: true
            Layout.columnSpan: 2

            Controls.Button {
                text: qsTr("Download")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission && mission.vehicle.length
                onClicked: mission.download()
            }

            Controls.Button {
                text: qsTr("Upload")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission && mission.vehicle.length
                onClicked: mission.upload()
            }

            Controls.Button {
                text: qsTr("Cancel")
                visible: false
            }

            Controls.Button {
                text: qsTr("Remove")
                borderColor: Controls.Theme.colors.controlBorder
                highlightColor: Controls.Theme.colors.negative
                hoverColor: highlightColor
                onClicked: {
                    collapse();
                    controller.removeMission(mission);
                }
            }

            Controls.Button {
                text: qsTr("Close")
                borderColor: Controls.Theme.colors.controlBorder
                onClicked: {
                    controller.saveMission(mission);
                    collapse();
                }
            }
        }
    }
}
