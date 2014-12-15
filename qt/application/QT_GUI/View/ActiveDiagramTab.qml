import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0
import "."

Rectangle {
    id: outerRect
    color: Style.tabBackgroundColor
    anchors.fill: parent
    anchors.margins: 5

    states:
    [

        State
        {
            name: "INIT_DIAGRAMM"
        },

        State
        {
            name: "BEGIN_UPDATE_DIAGRAMM"
        },

        State
        {
            name: "END_UPDATE_DIAGRAMM"
        }
    ]

    Rectangle {
        id: innerRect
        color: "transparent"

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;

        width: parent.width
        height: parent.height - 10

        anchors.topMargin: 5
        anchors.bottomMargin: 5

        GroupBox {
            id: grpPulsChart
            title: qsTr("Pulse flow over time:")
            anchors.left: parent.left
            height: parent.height
            width: parent.width / 2 - 10

            CustomPlotLineChart
            {
                state: "INIT_DIAGRAMM"
                id: customPlot

                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                objectName: "activeDiagramName"
                onStateChanged: { updateDataAndGUI() }
                Component.onCompleted: initCustomPlot()
            }
        }

        GroupBox {
            title: qsTr("Raw data:")
            anchors.right: parent.right

            height: parent.height
            width: parent.width / 2 - 10


            TableView {
                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                model: activeSensorDataModel

                TableViewColumn
                {
                    role: "activeDate";
                    title: qsTr("Date");
                    width: 200
                }

                TableViewColumn
                {
                    role: "activeHeartRate";
                    title: qsTr("HeartRate");
                    width: 100
                }

                itemDelegate:
                Item {
                    Text {
                        color: Style.tableViewTextColor
                        text: styleData.value
                    }
                }
            }
        }
    }
}
