import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

Item {
    id: root

    property var mission
    property bool renameMode: false

    signal collapse()

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: Controls.Theme.spacing

        RowLayout {
            spacing: Controls.Theme.spacing

            Controls.Button {
                flat: true
                iconSource: "qrc:/icons/left.svg"
                tipText: qsTr("Back to missions")
                onClicked: {
                    controller.saveMission(mission);
                    collapse();
                }
            }

            Controls.Label {
                text: mission ? mission.name : ""
                visible: !renameMode
                Layout.fillWidth: true

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: renameMode = true
                }
            }

            Controls.TextField {
                id: nameEdit
                visible: renameMode
                flat: true
                Binding on text { value: mission ? mission.name : ""; when: !nameEdit.activeFocus }
                onEditingFinished: {
                    mission.setName(text);
                    renameMode = false;
                }
                Layout.fillWidth: true
                Layout.fillHeight: true

            }

            Controls.ComboBox {
                id: vehiclesCombo
                flat: true
                labelText: qsTr("Vehicle")
                model: controller.vehicles
                displayText: mission ? mission.vehicle : ""
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
        }

        Route {
            route: mission ? mission.toJson(true).route : null
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
