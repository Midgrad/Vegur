import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Controls.Popup {
    id: root

    closePolicy: Controls.Popup.NoAutoClose
    width: Controls.Theme.baseSize * 15
    height: Math.min(implicitHeight, main.availableHeight)

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
                    mission: controller.mission(modelData)
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
