import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
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
        anchors.topMargin: 3

        width: parent.width
        height: parent.height / 3 - 15

        ComboBox {
            id: cmbSelectMeasuremode
            width: 200
            height: 20

            /*style: ComboBoxStyle {
                    background: Rectangle {
                    width: cmbSelectMeasuremode.width
                    height: 30
                    color: "red"
                }
            }*/

            anchors.leftMargin: 5
            currentIndex: 0
            model: ListModel {
                id: cbItems
                ListElement { text: "Activity" }
                ListElement { text: "Rest" }
            }

            //onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).text + ", " + currentIndex)
        }

        GroupBox {
            id: grpPastMeasurements
            title: qsTr("Recent and past measurements:")
            anchors.left: parent.left
            anchors.top: cmbSelectMeasuremode.bottom
            anchors.topMargin: 5
            height: parent.height - cmbSelectMeasuremode.height - anchors.topMargin
            width: parent.width

            TableView {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 5
                anchors.topMargin: 5

                width: parent.width - 10;
                height: parent.height - anchors.leftMargin - anchors.topMargin;

                Component {
                    id: checkBoxDelegate

                    Item {
                        CheckBox {
                            id: cbCheckBox
                            anchors.fill: parent
                            checked: styleData.value
                        }
                    }
                }

                TableViewColumn
                {
                    title: qsTr("");
                    role: "isSelected"
                    delegate: checkBoxDelegate
                }

                TableViewColumn
                {
                    title: qsTr("Date");
                    role: "measurementData"
                }

                TableViewColumn
                {
                    title: qsTr("Time");
                    role: "measurementTime"
                }

                TableViewColumn
                {
                    title: qsTr("Duration");
                    role: "measurementDuration"
                }
            }
        }
    }

    Rectangle {
        id: lowerRect
        color: "transparent"

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;

        width: parent.width
        height: parent.height / 3 * 2

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
                    width: 200
                }

                TableViewColumn
                {
                    role: "inactiveHeartRate";
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
    } // innerRect
}
