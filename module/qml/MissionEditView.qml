import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Item {
    id: root

    property bool renameMode: false
    readonly property var mission : controller.mission

    property alias missionId : controller.missionId

    signal collapse()

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    MissionController { id: controller }

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
                    controller.save();
                    collapse();
                }
            }

            Controls.Label {
                text: mission.name ? mission.name : ""
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

            Controls.Label {
                text: mission.type  ? mission.type : ""
                type: Controls.Theme.Label
            }

            Controls.ComboBox {
                id: vehiclesCombo
                flat: true
                labelText: qsTr("Vehicle")
                model: controller.vehicles
                displayText: mission ? mission.vehicle : ""
                onActivated: controller.assign(currentItem)
            }
        }

        Controls.ProgressBar {
            id: progress
            flat: true
            radius: Controls.Theme.rounding
            from: 0
            visible: !controller.complete
            to: controller.total
            value: controller.progress
            Layout.fillWidth: true

            Controls.Button {
                anchors.fill: parent
                flat: true
                tipText: qsTr("Cancel")
                text: progress.value + "/" + progress.to
                onClicked: controller.cancel()
            }
        }

        Controls.ButtonBar {
            id: bar
            flat: true
            visible: controller.complete
            Layout.fillWidth: true

            Controls.Button {
                text: qsTr("Download")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission.vehicle ? mission.vehicle.length : false
                onClicked: controller.download()
            }

            Controls.Button {
                text: qsTr("Upload")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission.vehicle ? mission.vehicle.length : false
                onClicked: controller.upload()
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
                    controller.remove();
                    collapse();
                }
            }
        }

        RouteView {
            route: mission ? mission.route : null
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
