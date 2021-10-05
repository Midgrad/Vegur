import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets

ColumnLayout {
    id: root

    property var route

    spacing: Controls.Theme.spacing

    Controls.Button {
        text: qsTr("Route")
        flat: true
        iconSource: waypointsList.visible ? "qrc:/icons/minus.svg" : "qrc:/icons/plus.svg"
        onClicked: waypointsList.visible = !waypointsList.visible
        Layout.fillWidth: true
    }

    Widgets.ListWrapper {
        id: waypointsList
        visible: false
        model: route ? route.waypoints : []
        emptyText: qsTr("No Waypoints")
        delegate: Widgets.ListItem {
            width: parent.width
            color: "transparent"
            expanded: waypointsList.currentIndex === index
            collapsedItem: WaypointView {
                waypointIndex: index
                waypoint: modelData
                onExpand: waypointsList.currentIndex = index
            }
            expandedItem: WaypointEditView {
                waypoint: modelData
                onCollapse: waypointsList.currentIndex = -1
            }
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
