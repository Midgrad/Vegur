import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

RowLayout {
    id: root

    property string routeId
    property var route: controller.routeData(routeId)

    Connections {
        target: controller
        onRouteChanged: if (routeId == root.routeId) route = controller.routeData(routeId)
    }

    spacing: 0
    state: "idle"
    states: [
        State { name: "idle" },
        State { name: "remove" },
        State { name: "rename" }
    ]

    Controls.Label {
        text: route.name
        visible: root.state != "rename"
        Layout.fillWidth: true

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: root.state = "rename"
        }
    }

    Controls.TextField {
        visible: root.state == "rename"
        onVisibleChanged: {
            if (!visible) return;

            text = route.name;
            forceActiveFocus();
            selectAll();
        }
        onHighlightedChanged: if (!highlighted) root.state = "idle"
        onEditingFinished: {
            controller.renameRoute(routeId, text);
            root.state = "idle";
        }
        Layout.fillWidth: true
    }

    Controls.Button {
        flat: true
        rightCropped: true
        iconSource: "qrc:/icons/center.svg"
        onClicked: controller.centerRoute(routeId)
    }

    Controls.Button {
        flat: true
        leftCropped: true
        rightCropped: true
        tipText: route.visible ? qsTr("Hide route") : qsTr("Show route")
        iconSource: route.visible ? "qrc:/icons/password_show.svg" : "qrc:/icons/password_hide.svg"
        onClicked: controller.modifyRoute(routeId, "visible", !route.visible)
    }

    Controls.Button {
        flat: true
        leftCropped: true
        visible: root.state != "remove"
        iconSource: "qrc:/icons/remove.svg"
        onClicked: root.state = "remove"
    }

    Controls.Button {
        flat: true
        leftCropped: true
        rightCropped: true
        visible: root.state == "remove"
        type: Controls.Theme.Negative
        iconSource: "qrc:/icons/remove.svg"
        onClicked: controller.removeRoute(routeId)
    }

    Controls.Button {
        flat: true
        leftCropped: true
        visible: root.state == "remove"
        type: Controls.Theme.Secondary
        iconSource: "qrc:/icons/cancel.svg"
        onClicked: root.state = "idle"
    }
}
