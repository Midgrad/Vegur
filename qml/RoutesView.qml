import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Vegur 1.0

Controls.Button {
    id: root

    RoutesController { id: controller }

    Component.onCompleted: map.registerController("routesController", controller)

    iconSource: "qrc:/icons/route.svg"
    tipText: qsTr("Routes")
    highlighted: popup.visible
    onClicked: popup.visible ? popup.close() : popup.open()

    Controls.Popup {
        id: popup

        closePolicy: Controls.Popup.CloseOnPressOutsideParent
        width: Controls.Theme.baseSize * 10
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
                    placeholderText: qsTr("Filter routes")
                    Layout.fillWidth: true
                }

                Controls.MenuButton {
                    flat: true
                    iconSource: "qrc:/icons/plus.svg"
                    model: controller.routeTypes
                    delegate: Controls.MenuItem {
                        text: modelData.name
                        onTriggered: controller.createRoute(modelData)
                    }
                }
            }

            Widgets.ListWrapper {
                id: list
                model: controller.routes
                emptyText: qsTr("No routes")
                delegate: Route {
                    width: parent.width
                    height: visible ? implicitHeight : 0
                    visible: route.name && route.name.includes(filterField.text)
                    route: modelData
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
