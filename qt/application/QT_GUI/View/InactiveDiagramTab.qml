import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
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
        id: upperRect
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
                    id: cmbSelectMeasuremode2
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

                 id: inactiveListDelegate
                 Item {
                     width: parent.width - 10
                     height: listView1.height/listView1.count
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

        GroupBox {
            id: groupBox1

            anchors.left: parent.left

            height: parent.height
            width: parent.width / 2 - 10

            title: qsTr("Inactive Heartrate Details")

            ListView {
                        id: listView1

                        height: parent.height
                        width: parent.width

                        anchors.right: parent.right
                        anchors.top: parent.top

                        model: inactiveSensorCalcModel
                        interactive: false
                        delegate: inactiveListDelegate
           }
        }
    }

    Rectangle {
        id: lowerRect
        color: "transparent"

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;

        width: parent.width
        height: parent.height / 4 * 3

        anchors.bottomMargin: 5

        GroupBox {
            id: grpPulsChart
            title: qsTr("Pulse chart:")
            anchors.left: parent.left
            height: parent.height
            width: parent.width / 2 - 10

            CustomPlotBarChart {
                state: "INIT_DIAGRAMM"
                id: customPlot

                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                objectName: "inactiveDiagramName"

                onStateChanged: { updateDataAndGUI() }
                Component.onCompleted: { initCustomPlot() }
            }
        }

        GroupBox {
            title: qsTr("Raw data:")
            anchors.right: parent.right

            height: parent.height
            width: parent.width / 2 - 10

            TableView {

                id: inactiveTableId
                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                model: inactiveSensorDataModel

                TableViewColumn
                {
                    role: "inactiveDate";
                    title: qsTr("Date");
                    width: inactiveTableId.width/3 * 2
                }

                TableViewColumn
                {
                    role: "inactiveHeartRate";
                    title: qsTr("HeartRate");
                   width: inactiveTableId.width/3
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
    } // innerRect
}
