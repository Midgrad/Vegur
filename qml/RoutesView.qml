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

    Controls.ButtonGroup { buttons: modeRow.children }

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

                RowLayout {
                    id: modeRow
                    spacing: 0

                    Controls.Button {
                        id: filterMode
                        flat: true
                        rightCropped: true
                        checkable: true
                        checked: true
                        iconSource: "qrc:/icons/filter.svg"
                        onClicked: filterField.forceActiveFocus()
                    }

                    Controls.Button {
                        id: addMode
                        flat: true
                        leftCropped: true
                        checkable: true
                        iconSource: "qrc:/icons/plus.svg"
                        onClicked: nameField.forceActiveFocus()
                    }
                }

                Controls.FilterField {
                    id: filterField
                    flat: true
                    placeholderText: qsTr("Filter routes")
                    visible: filterMode.checked
                    onVisibleChanged: clear()
                    onTextChanged: controller.filter(text)
                    Layout.fillWidth: true
                }

                Controls.TextField {
                    id: nameField
                    flat: true
                    placeholderText: qsTr("Route filename")
                    visible: addMode.checked
                    isValid: text.length > 3 && !controller.routes.includes(text)
                    Layout.fillWidth: true
                }

                Controls.Button {
                    flat: true
                    enabled: nameField.isValid
                    visible: addMode.checked
                    iconSource: "qrc:/icons/ok.svg"
                    onClicked: {
                        controller.createRoute(nameField.text);
                        nameField.clear();
                    }
                }
            }

            Widgets.ListWrapper {
                id: list
                model: controller.routes
                emptyText: qsTr("No routes")
                delegate: Route {
                    width: parent.width
                    route: modelData
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
