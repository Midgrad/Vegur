import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

Item {
    id: root

    property var mission: null
    property var missionStatus: controller.missionStatus(mission.id)

    property bool missionPropertiesVisible: true
    property bool routePropertiesVisible: false

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

        // TODO: ListButton
        Controls.Button {
            text: qsTr("Mission")
            flat: true
            iconSource: missionPropertiesVisible ? "qrc:/icons/down.svg" : "qrc:/icons/right.svg"
            onClicked: missionPropertiesVisible = !missionPropertiesVisible
            Layout.fillWidth: true
        }

        Widgets.PropertyTable {
            visible: missionPropertiesVisible
            flat: true
            labelWidth: Controls.Theme.baseSize * 6
            Layout.fillWidth: true

            Controls.TextField {
                id: nameEdit
                labelText: qsTr("Name")
                Binding on text { value: mission.name ? mission.name : ""; when: !nameEdit.activeFocus }
                onEditingFinished: controller.saveMission(mission.id, { name: text });
            }

            Controls.ComboBox {
                id: vehiclesCombo
                flat: true
                labelText: qsTr("Vehicle")
                model: controller.vehicles
                displayText: mission ? mission.vehicle : ""
                onActivated: controller.assign(mission.id, currentItem)
            }

            Controls.ComboBox {
                labelText: qsTr("Type")
                displayText: mission.type ? mission.type : ""
            }
        }

        Controls.ProgressBar {
            id: progress
            visible: !missionStatus.complete && missionPropertiesVisible
            flat: true
            radius: Controls.Theme.rounding
            from: 0
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
            visible: missionStatus.complete && missionPropertiesVisible
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

        // TODO: ListButton
        Controls.Button {
            flat: true
            text: qsTr("Route")
            iconSource: routePropertiesVisible ? "qrc:/icons/down.svg" : "qrc:/icons/right.svg"
            onClicked: routePropertiesVisible = !routePropertiesVisible
            Layout.fillWidth: true
        }

        RouteView {
            id: routeList
            visible: routePropertiesVisible
            route: controller.route(mission.id)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
