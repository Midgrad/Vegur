import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Controls.Button {
    id: root

    property var selectedMission: null

    MissionListController { id: listController }

    Component.onCompleted: map.registerController("missionsController", listController)

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
        onClosed: missionsList.currentIndex = -1

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
                    model: listController.missionTypes
                    delegate: Controls.MenuItem {
                        text: modelData
                        onTriggered: listController.addNewMission(modelData)
                    }
                }
            }

            Widgets.ListWrapper {
                id: missionsList
                visible: selectedMission === null
                emptyText: qsTr("No Missions")
                model: listController.missions
                delegate: MissionView {
                    width: parent.width
                    height: visible ? implicitHeight : 0
                    visible: mission && mission.name.includes(filterField.text)
                    mission: modelData
                    onExpand: selectedMission = mission
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            MissionEditView {
                visible: selectedMission !== null
                missionId: selectedMission ? selectedMission.id : null
                onCollapse: {
                    missionsList.forceActiveFocus();
                    selectedMission = null;
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
