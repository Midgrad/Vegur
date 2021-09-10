import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Controls.Button {
    id: root

    MissionsController {
        id: controller
    }

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
                    model: controller.vehicles
                    delegate: Controls.MenuItem {
                        text: modelData
                        onTriggered: controller.addNewMission(modelData)
                    }
                }
            }

            Widgets.ListWrapper {
                id: list
                model: controller.missions
                emptyText: qsTr("No Missions")
                delegate: Widgets.ListItem {
                    id: listItem
                    width: parent.width
                    color: "transparent"
                    expanded: list.currentIndex === index

                    collapsedItem: Mission {
                        mission: model.entity
                        onExpand: list.currentIndex = index
                        opacity: list.currentIndex == -1 ? 1 : 0.5
                    }

                    expandedItem: MissionEdit {
                        mission: model.entity
                        onCollapse: list.currentIndex = -1
                    }
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
