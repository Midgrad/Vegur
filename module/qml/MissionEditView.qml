import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

Item {
    id: root

    property bool renameMode: false
    property var mission: null
    property var missionStatus: controller.missionStatus(mission.id)

    signal collapse()

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    Connections {
        target: controller
        onMissionChanged: if (missionId === mission.id) mission = controller.mission(missionId)
        onMissionStatusChanged: if (missionId === mission.id) missionStatus = status
    }

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
                onClicked: collapse()
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
                    controller.saveMission(mission.id, { name: text });
                    renameMode = false;
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Controls.Label {
                text: mission.type ? mission.type : ""
                type: Controls.Theme.Label
            }

            Controls.ComboBox {
                id: vehiclesCombo
                flat: true
                labelText: qsTr("Vehicle")
                model: controller.vehicles
                displayText: mission ? mission.vehicle : ""
                onActivated: controller.assign(mission.id, currentItem)
            }
        }

        Controls.ProgressBar {
            id: progress
            flat: true
            radius: Controls.Theme.rounding
            from: 0
            visible: !missionStatus.complete
            to: missionStatus.total
            value: missionStatus.progress
            Layout.fillWidth: true

            Controls.Button {
                anchors.fill: parent
                flat: true
                tipText: qsTr("Cancel")
                text: progress.value + "/" + progress.to
                onClicked: controller.cancel(mission.id)
            }
        }

        Controls.ButtonBar {
            id: bar
            flat: true
            visible: missionStatus.complete
            Layout.fillWidth: true

            Controls.Button {
                text: qsTr("Download")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission.vehicle ? mission.vehicle.length : false
                onClicked: controller.download(mission.id)
            }

            Controls.Button {
                text: qsTr("Upload")
                borderColor: Controls.Theme.colors.controlBorder
                enabled: mission.vehicle ? mission.vehicle.length : false
                onClicked: controller.upload(mission.id)
            }

            Controls.Button {
                text: qsTr("Remove")
                borderColor: Controls.Theme.colors.controlBorder
                highlightColor: Controls.Theme.colors.negative
                hoverColor: highlightColor
                onClicked: {
                    controller.remove(mission.id);
                    collapse();
                }
            }
        }

        RouteView {
            route: controller.route(mission.id)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
