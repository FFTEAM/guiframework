import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0
import "."

Rectangle {
    id: outerRect
    /*color: "#f3f3f3"
    radius: 3
    border.color: "#d1d1d1"
    border.width: 1*/
    color: "transparent"
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

        GroupBox {
            id: grpPastMeasure
            title: qsTr("Recent and past measurements:")
            anchors.left: parent.left
            height: parent.height
            width: parent.width

            ComboBox {
                currentIndex: 0
                model: ListModel {
                    id: cbItems
                    ListElement { text: "Banana"; color: "Yellow" }
                    ListElement { text: "Apple"; color: "Green" }
                    ListElement { text: "Coconut"; color: "Brown" }
                }
                width: 200
                onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
            }

            /*TableView {
                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

                Component {
                    id: checkBoxDelegate

                    Item {
                        CheckBox {
                            anchors.fill: parent
                            checked: styleData.value
                        }
                    }
                }

                TableViewColumn
                {
                    title: qsTr("name");
                    role: "isDoneStateCheckState"
                    delegate: checkBoxDelegate
                }

                TableViewColumn
                {
                    title: qsTr("Date");
                }
            }*/

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
                         Text{
                                color: "blue"
                                text: styleData.value
                         }

                }
            }
        }
    } // innerRect
}
