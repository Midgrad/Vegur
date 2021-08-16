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
        x: root.x

        Widgets.ListWrapper {
            model: controller.adsb
            anchors.fill: parent
            emptyText: qsTr("No routes")

            delegate: Controls.Label {
                width: parent.width
                text: modelData.name
            }
        }
    }
}
