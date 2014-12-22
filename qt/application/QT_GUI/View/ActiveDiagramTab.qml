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
        id: upperRectid
        color: "transparent"

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.topMargin: 7

        width: parent.width
        height: parent.height / 4 - 15

        GroupBox {
            id: grpFilter
            objectName: "selectionGrpName"
            title: qsTr("Filtering options")

            anchors.right: parent.right
            height: parent.height
            width: parent.width / 2 - 10

            Rectangle {
                id: yearRect
                objectName: "yearRectName"

                state: "BEGIN_SELECTION"

                color: "transparent"
                width: parent.width
                height: parent.height / 3
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

            Rectangle {
                id: weekRect
                objectName: "weekRectName"
                color: "transparent"
                width: parent.width
                height: parent.height / 3
                anchors.top: monthRect.bottom
                anchors.topMargin: 3

                visible:  false

                Label {
                    id: weekLabelId
                    anchors.left: parent.left
                    height: cmbSelectWeekFilter.height
                    width: parent.width / 6
                    text: qsTr("Week:")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    renderType: Text.NativeRendering
                }

                ComboBox {
                    id: cmbSelectWeekFilter
                    objectName: "cmbSelectWeekFilterName"

                    signal onComboboxPressed(string text);

                    anchors.left: weekLabelId.right
                    anchors.leftMargin: 10
                    width: parent.width - weekLabelId.width - 10
                    currentIndex: 0
                    model: activeSelectionWeekModel
                }
            }
        } // grpFilter

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
                        renderType: Text.NativeRendering
                    }
                    Text {
                        text: activeCalcValue
                        anchors.verticalCenter: parent.verticalCenter
                        width: (parent.width - 10)/2
                        renderType: Text.NativeRendering
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

        width: parent.width
        height: parent.height / 4 * 3

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
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
                            role: "date";
                            title: qsTr("Date");
                            width: parent.width/3 * 2
                        }
                        TableViewColumn
                        {
                            role: "heartRate";
                            title: qsTr("HeartRate");
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

        GroupBox {
            title: qsTr("Raw data:")
            anchors.right: parent.right

            height: parent.height
            width: parent.width / 2 - 10

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
                    width: tableRunId.width/3 * 2
                }
                TableViewColumn
                {
                    role: "heartRate";
                    title: qsTr("HeartRate");
                    width: tableRunId.width/3
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
}
