import QtQuick 2.6
import QtQuick.Layouts 1.12
import Industrial.Controls 1.0 as Controls

RowLayout {
    id: row

    property var route
    property bool yesNo: false

    spacing: 0

    Controls.Label {
        text: route
        Layout.fillWidth: true
    }

    Controls.Button {
        flat: true
        rightCropped: true
        iconSource: "qrc:/icons/center.svg"
    }

    Controls.Button {
        flat: true
        leftCropped: true
        rightCropped: true
        iconSource: "qrc:/icons/password_hide.svg"
    }

    Controls.Button {
        flat: true
        leftCropped: true
        visible: !yesNo
        iconSource: "qrc:/icons/remove.svg"
        onClicked: yesNo = true
    }

    Controls.Button {
        flat: true
        leftCropped: true
        rightCropped: true
        visible: yesNo
        type: Controls.Theme.Negative
        iconSource: "qrc:/icons/remove.svg"
        onClicked: controller.removeRoute(route)
    }

    Controls.Button {
        flat: true
        leftCropped: true
        visible: yesNo
        type: Controls.Theme.Secondary
        iconSource: "qrc:/icons/cancel.svg"
        onClicked: yesNo = false
    }
}
