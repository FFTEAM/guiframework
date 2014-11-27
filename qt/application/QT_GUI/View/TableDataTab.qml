import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {

    id: rectangle1
    objectName: "recName"
    width: 600
    height: 400
    color: "#dcc3af"

        TableView {
            x: 89
            y: 60

            width: 450
            height: 238
            anchors.horizontalCenterOffset: -6
            anchors.horizontalCenter: parent.horizontalCenter
            model: sensorDataModel

            TableViewColumn
            {
                role: "date";
                title: qsTr("Date");
                width: 200
            }

            TableViewColumn
            {
                role: "heartRate";
                title: qsTr("HeartRate");
                width: 100
            }

            TableViewColumn
            {
                role: "stepLength";
                title: qsTr("StepLength");
                width: 100
            }

            itemDelegate:
            Item {
                     Text{
                            color: "blue"
                            text: styleData.value
                     }

            }
        }

        Button{

            objectName: "printButtonName"
            signal printButtonIsPressed();
            id: printButtonID
            x: 240
            y: 217
            width: 80
            height: 35
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 29
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked:
            {
                printButtonIsPressed();
            }

            Text{ x: 0; y: 0; width: 80; height: 35;text: qsTr("print") ; anchors.bottom: parent.bottom; anchors.bottomMargin: 1; anchors.horizontalCenter: parent.horizontalCenter; verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter }
        }
}
