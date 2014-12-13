import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Dialog {
    visible: true
    title: qsTr("Settings");

    contentItem: Rectangle {
        color: "#000000";
        implicitWidth: 600
        implicitHeight: 400

        Text {
            text: "GEIL"
            color: "#ffffff"
            anchors.centerIn: parent
        }
    }
}
