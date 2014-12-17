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

    Component {

             id: inactiveListDelegate
             Item {
                 width: parent.width - 10
                 height: 70
                 Row {
                      spacing: 2
                      width: parent.width - 10

                      Text {
                          text: inactiveCalcDescription
                          anchors.verticalCenter: parent.verticalCenter
                          width: (parent.width - 10)/2
                      }

                      Text {
                          text: inactiveCalcValue
                          anchors.verticalCenter: parent.verticalCenter
                          width: (parent.width - 10)/2
                      }
                 }
             }
    }

    Component {

             id: activeListDelegate
             Item {
                 width: parent.width - 10
                 height: 70
                 Row {
                      spacing: 2
                      width: parent.width - 10

                      Text {
                          text: activeCalcDescription
                          anchors.verticalCenter: parent.verticalCenter
                          width: (parent.width - 10)/2
                      }

                      Text {
                          text: activeCalcValue
                          anchors.verticalCenter: parent.verticalCenter
                          width: (parent.width - 10)/2
                      }
                 }
             }
    }

    GroupBox {
        id: groupBox1

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5

        height: parent.height / 2 - 10;
        width: parent.width - 10;

        title: qsTr("Inactive Heartrate Details")

        ListView {
                    id: listView1

                    height: parent.height;
                    width: parent.width - 10;

                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5

                    model: inactiveSensorCalcModel
                    interactive: false
                    delegate: inactiveListDelegate
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

        ListView {
                    id: listView2

                    height: parent.height;
                    width: parent.width - 10;

                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5

                    model: activeSensorCalcModel
                    interactive: false
                    delegate: activeListDelegate
       }


    }
}
