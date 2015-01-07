import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import CostumPlot 1.0
import "."

Rectangle {
    id: outerRect
    objectName: "outerRectName"
    color: Style.tabBackgroundColor
    anchors.fill: parent
    anchors.margins: 5

    Rectangle {
        id: leftRect
        color: "transparent"

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.topMargin: 7

        width: parent.width / 2 - 5
        height: parent.height

        Component {
            id: activeListDelegate
            Item {
                width: parent.width - 10
                height: listView2.height/ listView2.count
                Row {
                    spacing: 10
                    width: parent.width - 10
                    Label {
                        text: activeCalcDescription
                        anchors.verticalCenter: parent.verticalCenter
                        width: (parent.width)/10 * 5
                        renderType: Text.NativeRendering
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                    }
                    Label {
                        text: activeCalcValue
                        anchors.verticalCenter: parent.verticalCenter
                        width: (parent.width)/10 * 2
                        renderType: Text.NativeRendering
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                    }
                    Label {
                        text: activeCalcUnitOfMeasurement
                        anchors.verticalCenter: parent.verticalCenter
                        width: (parent.width)/10 * 3
                        renderType: Text.NativeRendering
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        GroupBox {
            id: grpDetails
            anchors.left: parent.left
            height: parent.height / 3
            width: parent.width

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

        GroupBox {
            id: grpPulsChart
            title: qsTr("Pulse flow over time:")
            anchors.left: parent.left
            anchors.top: grpDetails.bottom
            height: parent.height / 3 * 2 - 10
            width: parent.width

            TabView
            {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 5
                anchors.topMargin: 5

                width: parent.width - 10;
                height: parent.height - 10;

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

                Tab {
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
                            role: "measurepoint";
                            title: qsTr("Seconds since start");
                            width: parent.width/3
                        }
                        TableViewColumn
                        {
                            role: "heartRate";
                            title: qsTr("HeartRate");
                            width: parent.width/3
                        }

                        TableViewColumn
                        {
                            role: "stepCount";
                            title: qsTr("Steps");
                            width: parent.width/3
                        }

                        itemDelegate:
                        Item {
                            Text {
                                color: Style.tableViewTextColor
                                text: styleData.value
                                renderType: Text.NativeRendering
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: rightRect
        color: "transparent"

        width: parent.width / 2 - 5
        height: parent.height

        anchors.right: parent.right;
        anchors.top: parent.top
        anchors.topMargin: 7
        anchors.leftMargin: 2

        GroupBox {
            id: grpFilter
            objectName: "selectionGrpName"
            title: qsTr("Filtering options")

            anchors.right: parent.right
            height: parent.height / 3 * 1
            width: parent.width

            Rectangle {
                id: yearRect
                objectName: "yearRectName"

                color: "transparent"
                width: parent.width
                height: parent.height / 2
                anchors.top: parent.top
                anchors.topMargin: 3

                Label {
                    id: yearLabelId
                    anchors.left: parent.left
                    height: cmbSelectYearFilter.height
                    width: parent.width / 6
                    text: qsTr("Year:")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    renderType: Text.NativeRendering
                }

                ComboBox {

                    id: cmbSelectYearFilter
                    objectName: "cmbSelectYearFilterName"

                    signal onComboboxPressed(string text);

                    anchors.left: yearLabelId.right
                    anchors.leftMargin: 10
                    width: parent.width - yearLabelId.width - 10
                    currentIndex: 0
                    model: activeSelectionYearModel

                    onPressedChanged: {

                        onComboboxPressed(currentText);
                    }
                }
            }

            Rectangle {
                id: monthRect
                objectName: "monthRectName"
                color: "transparent"
                width: parent.width
                height: parent.height / 3
                anchors.top: yearRect.bottom
                anchors.topMargin: 3

                visible: false

                Label {
                    id: monthLabelId
                    anchors.left: parent.left
                    height: cmbSelectMonthFilter.height
                    width: parent.width / 6
                    text: qsTr("Month:")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    renderType: Text.NativeRendering
                }

                ComboBox {
                    id: cmbSelectMonthFilter
                    objectName: "cmbSelectMonthFilterName"

                    signal onComboboxPressed(string text);

                    anchors.left: monthLabelId.right
                    anchors.leftMargin: 10
                    width: parent.width - monthLabelId.width - 10
                    currentIndex: 0
                    model: activeSelectionMonthModel

                    onPressedChanged:
                    {
                        onComboboxPressed(currentText);
                    }
              }
            }
        } // grpFilter


        GroupBox {
            title: qsTr("Raw data:")
            anchors.right: parent.right
            anchors.top: grpFilter.bottom
            //anchors.bottom: parent.bottom

            height: parent.height / 3 * 2 - 10
            width: parent.width

            TableView {

                id: tableRunId
                objectName: "tableRunName"
                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                model: activeSensorTableModel

                onSelectionChanged:
                {
                    clicked(currentRow);
                }

                TableViewColumn
                {
                    role: "date";
                    title: qsTr("Date");
                    width: tableRunId.width/4 * 2
                }
                TableViewColumn
                {
                    role: "heartRate";
                    title: qsTr("heart rate");
                    width: tableRunId.width/4
                }
                TableViewColumn
                {
                    role: "stepCount";
                    title: qsTr("Step count");
                    width: tableRunId.width/4
                }

                itemDelegate:
                Item {
                    Text {
                        color: Style.tableViewTextColor
                        text: styleData.value
                        renderType: Text.NativeRendering
                    }
                }
            }
        }
    }
}
