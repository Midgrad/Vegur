import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Controls.Button {
    id: root

    property var selectedMission: null

    MissionsController { id: controller }

    Component.onCompleted: map.registerController("missionsController", controller)

    iconSource: "qrc:/icons/mission.svg"
    tipText: qsTr("Missions")
    highlighted: popup.visible
    onClicked: popup.visible ? popup.close() : popup.open()

    Controls.Popup {
        id: popup

        closePolicy: Controls.Popup.CloseOnPressOutsideParent
        width: Controls.Theme.baseSize * 15
        height: Math.min(implicitHeight, main.availableHeight)
        y: root.height + Controls.Theme.margins
        x: -root.parent.x

        ColumnLayout {
            anchors.fill: parent
            spacing: Controls.Theme.spacing

            RowLayout {
                visible: selectedMission === null
                spacing: Controls.Theme.spacing

                Controls.FilterField {
                    id: filterField
                    flat: true
                    placeholderText: qsTr("Filter missions")
                    Layout.fillWidth: true
                }

                Controls.MenuButton {
                    flat: true
                    iconSource: "qrc:/icons/plus.svg"
                    model: controller.missionTypes
                    delegate: Controls.MenuItem {
                        text: modelData
                        onTriggered: controller.addNewMission(modelData)
                    }
                }
            }

            Loader {
                sourceComponent: selectedMission ? missionEdit : missionsList
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Component {
                id: missionsList
                Widgets.ListWrapper {
                    emptyText: qsTr("No Missions")
                    model: controller.missions
                    delegate: MissionView {
                        width: parent.width
                        height: visible ? implicitHeight : 0
                        visible: mission && mission.name.includes(filterField.text)
                        mission: modelData
                        onExpand: selectedMission = mission
                    }
                }
            }

            Component {
                id: missionEdit
                MissionEditView {
                    mission: selectedMission
                    onCollapse: selectedMission = null
                }
            }
        }
    }
}
