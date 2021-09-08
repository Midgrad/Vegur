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

                Controls.Button {
                    flat: true
                    iconSource: "qrc:/icons/plus.svg"
                    onClicked: controller.addNewMission()
                }

//                Controls.MenuButton {
//                    flat: true
//                    iconSource: "qrc:/icons/plus.svg"
//                    model: controller.routeTypes
//                    delegate: Controls.MenuItem {
//                        text: controller.routeTypeData(modelData).name
//                        onTriggered: controller.createRoute(modelData)
//                    }
//                }
            }

            Widgets.ListWrapper {
                id: list
                model: controller.missions
                emptyText: qsTr("No Missions")
                delegate: Mission {
                    width: parent.width
                    mission: model.entity
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
