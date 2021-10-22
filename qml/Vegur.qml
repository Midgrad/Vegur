import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

Item {
    id: root

    property var selectedMission: null

    onSelectedMissionChanged: controller.editRoute(selectedMission ? selectedMission.id : null)
    Component.onCompleted: map.registerController("missionsController", controller)

    implicitWidth: row.implicitWidth
    implicitHeight: row.implicitHeight

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: 1

        Controls.Button {
            id: backButton
            iconSource: "qrc:/icons/left.svg"
            tipText: qsTr("Back to missions")
            highlighted: missionList.visible
            rightCropped: true
            visible: selectedMission
            onClicked: selectedMission = null
        }

        Controls.Button {
            iconSource: "qrc:/icons/route.svg"
            text: missionList.visible ? selectedMission ? selectedMission.name : qsTr("Missions") : ""
            tipText: missionList.visible ? qsTr("Close") : qsTr("Open")
            highlighted: missionList.visible
            leftCropped: backButton.visible
            onClicked: missionList.visible ? missionList.close() : missionList.open()
        }
    }

    MissionListView {
        id: missionList
        y: root.height + Controls.Theme.margins
        x: -root.parent.x
    }
}
