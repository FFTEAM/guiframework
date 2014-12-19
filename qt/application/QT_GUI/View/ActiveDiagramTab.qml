import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
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
        id: upperRectid
        color: "transparent"

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.topMargin: 7

        width: parent.width
        height: parent.height / 4 - 15

        ColumnLayout {

            id: column1
            anchors.right: parent.right
            height: parent.height
            width: parent.width / 2 - 10

            Row {

                id: yearRowId
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                height: parent.height / 3 - 15
                anchors.top: parent.top
                anchors.topMargin: 20
                width: parent.width - 250

                Label{

                    id: yearLabelId
                    height: parent.height
                    width: parent.width / 4
                    text: qsTr("Year")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                ComboBox {
                    id: cmbSelectMeasuremode
                    width: parent.width / 4 * 3
                    height: parent.height
                    currentIndex: 0
                    model: ListModel {
                        id: cbItems
                        ListElement { text: "2014" }
                        ListElement { text: "2013" }
                        ListElement { text: "2012" }
                        ListElement { text: "2011" }
                    }
                }

            }

            Row {

                id: monthRowId
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                height: parent.height / 3 - 15
                anchors.top: yearRowId.bottom
                anchors.topMargin: 10
                width: parent.width - 250

                Label{

                    height: parent.height
                    width: parent.width / 4
                    text: qsTr("Month")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                ComboBox {
                    id: cmbSelectMeasuremode1
                    width: parent.width / 4 * 3
                    height: parent.height
                    currentIndex: 0
                    model: ListModel {
                        id: cbItems1
                        ListElement { text: "Januar" }
                        ListElement { text: "März" }
                        ListElement { text: "Oktober" }
                        ListElement { text: "November" }
                    }
                }

            }

            Row {

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                height: parent.height / 3 - 15
                anchors.top: monthRowId.bottom
                anchors.topMargin: 10
                width: parent.width - 250

                Label{

                    height: parent.height
                    width: parent.width / 4
                    text: qsTr("Week")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                ComboBox {
                    id: cmbSelectMeasuremode3
                    width: parent.width / 4 * 3
                    height: parent.height
                    currentIndex: 0
                    model: ListModel {
                        id: cbItems2
                        ListElement { text: "1" }
                        ListElement { text: "2" }
                        ListElement { text: "3" }
                        ListElement { text: "4" }
                    }
                }
            }
        }

        Component {

                 id: activeListDelegate
                 Item {
                     width: parent.width - 10
                     height: listView2.height/ listView2.count
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
            id: groupBox2
            anchors.left: parent.left
            height: parent.height
            width: parent.width / 2 - 10

            title: qsTr("Active Heartrate Details")

            ListView {
                        id: listView2
                        height: parent.height
                        width: parent.width
                        anchors.right: parent.right
                        anchors.top: parent.top

                        model: activeSensorCalcModel
                        interactive: false
                        delegate: activeListDelegate
           }


        }
    }

    Rectangle {
        id: innerRect
        color: "transparent"

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;

        width: parent.width
        height: parent.height / 4 * 3

        anchors.topMargin: 5
        anchors.bottomMargin: 5

        GroupBox {
            id: grpPulsChart
            title: qsTr("Pulse flow over time:")
            anchors.left: parent.left
            height: parent.height
            width: parent.width / 2 - 10

            TabView
            {
                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                Tab{
                    id: tab1
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    anchors.bottomMargin: 7
                    anchors.topMargin: 12
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    title: qsTr("Chart")

                    CustomPlotLineChart
                    {
                        state: "INIT_DIAGRAMM"
                        id: customPlot

                        width: parent.width;
                        height: parent.height;

                        objectName: "activeDiagramName"
                        onStateChanged: { updateDataAndGUI() }
                        Component.onCompleted: initCustomPlot()
                    }
                }

                Tab{
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    anchors.bottomMargin: 7
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.topMargin: 12
                    title: qsTr("Data")

                    TableView
                    {
                        width: parent.width;
                        height: parent.height;

                        model: activeSensorDataModel

                        TableViewColumn
                        {
                            role: "activeDate";
                            title: qsTr("Date");
                            width: parent.width/3 * 2
                        }

                        TableViewColumn
                        {
                            role: "activeHeartRate";
                            title: qsTr("HeartRate");
                            width: parent.width/3
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

        GroupBox {
            title: qsTr("Raw data:")
            anchors.right: parent.right

            height: parent.height
            width: parent.width / 2 - 10


            TableView {

                id: tableId
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
                    width: tableId.width/3 * 2
                }

                TableViewColumn
                {
                    role: "activeHeartRate";
                    title: qsTr("HeartRate");
                    width: tableId.width/3
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
