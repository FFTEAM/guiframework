import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: rectangle1
    color: "#f3f3f3"
    radius: 3
    border.color: "#d1d1d1"
    border.width: 1
    anchors.fill: parent
    anchors.topMargin: 10
    anchors.bottomMargin: 10
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    GroupBox {
        id: groupBox1

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5

        height: parent.height / 2 - 10;
        width: parent.width - 10;

        title: qsTr("Inactive Heartrate Details")

        Label {
            id: label1
            x: 56
            y: 24
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label2
            x: 56
            y: 65
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label3
            x: 56
            y: 109
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label4
            x: 321
            y: 24
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label5
            x: 321
            y: 65
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label6
            x: 321
            y: 109
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    GroupBox {
        id: groupBox2

        anchors.top: groupBox1.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5

        height: parent.height / 2 - 10;
        width: parent.width - 10;

        title: qsTr("Active Heartrate Details")
        Label {
            id: label7
            x: 56
            y: 24
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label8
            x: 56
            y: 65
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label9
            x: 56
            y: 109
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label10
            x: 321
            y: 24
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label11
            x: 321
            y: 65
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: label12
            x: 321
            y: 109
            width: 120
            height: 23
            text: qsTr("Label")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
