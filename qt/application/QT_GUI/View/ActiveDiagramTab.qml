import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0

Rectangle {
    color: "#f3f3f3"
    radius: 3
    border.color: "#d1d1d1"
    border.width: 1
    anchors.fill: parent
    anchors.topMargin: 10
    anchors.bottomMargin: 10
    anchors.leftMargin: 10
    anchors.rightMargin: 10

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

    Text {
        anchors.left: parent.left
        anchors.top: parent.top

        anchors.leftMargin: 5
        anchors.topMargin: 5

        text: qsTr("Pulse flow over time:");
    }

    CustomPlotLineChart
    {
        state: "INIT_DIAGRAMM"
        id: customPlot

        anchors.left: parent.left
        anchors.top: parent.top

        width: parent.width / 2 - 20;
        height: parent.height - 30;

        anchors.leftMargin: 5
        anchors.rightMargin: 10
        anchors.topMargin: 25

        objectName: "activeDiagramName"
        onStateChanged: { updateDataAndGUI() }
        Component.onCompleted: initCustomPlot()
    }

    Text {
        anchors.left: parent.left
        anchors.top: parent.top

        anchors.leftMargin: parent.width / 2;
        anchors.topMargin: 5

        text: qsTr("Raw data:");
    }

    TableView {
        anchors.right: parent.right
        anchors.top: parent.top

        width: parent.width / 2;
        height: parent.height - 30;

        anchors.rightMargin: 5
        anchors.topMargin: 25

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
                color: "blue"
                text: styleData.value
            }
        }
    }
}
