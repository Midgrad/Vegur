import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

Item {
    id: root

    property var mission

    signal collapse()

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: Controls.Theme.spacing

        Widgets.PropertyTable {
            flat: true
            Layout.fillWidth: true
            labelWidth: width / 3

            Controls.TextField {
                id: nameEdit
                labelText: qsTr("Name")
                Binding on text { value: mission ? mission.name : ""; when: !nameEdit.activeFocus }
                onEditingFinished: mission.setName(text)
            }

            Controls.ComboBox {
                id: vehiclesCombo
                labelText: qsTr("Vehicle")
                model: controller.vehicles
                Binding on currentIndex {
                    value: mission ? controller.vehicles.indexOf(mission.vehicle) : -1
                    when: !vehiclesCombo.activeFocus
                }
                onActivated: controller.assignMission(mission, currentItem)
            }
        }

        Controls.ProgressBar {
            id: progress
            flat: true
            radius: Controls.Theme.rounding
            from: 0
            visible: mission && !mission.complete
            to: mission ? mission.total : 0
            value: mission ? mission.progress : 0
            Layout.fillWidth: true

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

        Controls.Button {
            text: qsTr("Route")
            flat: true
            iconSource: waypointsList.visible ? "qrc:/icons/minus.svg" : "qrc:/icons/plus.svg"
            onClicked: waypointsList.visible = !waypointsList.visible
            Layout.fillWidth: true
        }

        Widgets.ListWrapper {
            id: waypointsList
            visible: false
            model: mission ? mission.toJson().route.waypoints : []
            emptyText: qsTr("No Waypoints")
            Layout.fillWidth: true
            delegate: Controls.Label { text: modelData.name }
        }
    }
}
