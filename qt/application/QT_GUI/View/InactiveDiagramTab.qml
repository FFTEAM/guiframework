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


        GroupBox {
            id: grpFilter
            objectName: "grpFilterName"

            anchors.right: parent.right

            height: parent.height
            width: parent.width / 2 - 10

            title: qsTr("Filtering options")

            Row {
                id: startDateRow
                width: parent.width
                height: parent.height / 3 - 5
                anchors.top: parent.top
                anchors.topMargin: 3

                Label {
                    id: startDateLabel
                    height: startDateInput.height
                    width: parent.width / 6
                    text: qsTr("start date ")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                TextField{

                    id: startDateInput
                    objectName: "startDateInputName"
                    width: parent.width / 6 * 3
                    height: parent.height
                    style: TextFieldStyle {

                            textColor: "black"
                            background: Rectangle {
                                id: startDateValidateRec
                                border.color: "grey"
                                border.width: 1
                            }
                   }
                }

                Label{

                    id: startDateFormatLabel
                    height: startDateInput.height
                    width: parent.width / 6 * 2
                    text: qsTr("  (DD-MM-YYYY)")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Row {
                id: endDateRow
                width: parent.width
                height: parent.height / 3 - 5
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    id: endDateLabel
                    height: endDateInput.height
                    width: parent.width / 6
                    text: qsTr("end date ")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                TextField{

                    id: endDateInput
                    objectName: "endDateInputName"
                    width: parent.width / 6 * 3
                    height: parent.height
                    style: TextFieldStyle {

                            textColor: "black"
                            background: Rectangle {
                                id: endDateValidateRec
                                border.color: "grey"
                                border.width: 1
                            }
                   }
                }

                Label{

                    id: endDateFormatLabel
                    height: endDateInput.height
                    width: parent.width / 6 * 2
                    text: qsTr("  (DD-MM-YYYY)")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Row{

                id: filterButtonRow
                width: parent.width
                height: parent.height / 3 - 5
                anchors.bottom: parent.bottom

                Label
                {
                    id: errorLabel
                    objectName: "errorLabelName"
                    width: parent.width / 6 * 3
                    height: parent.height
                    color: "red"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }

                spacing : 3

                Button{
                    id: filterButton
                    objectName: "filerButtonName"
                    width: parent.width / 6
                    height: parent.height
                    text: qsTr("filter")
                }
            }

        } // grpFilter

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
                objectName: "inactiveDiagramName"

                anchors.left: parent.left
                anchors.top: parent.top

                width: parent.width - 10;
                height: parent.height - 10;

                anchors.leftMargin: 5
                anchors.topMargin: 5

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
                    role: "date";
                    title: qsTr("Date");
                    width: inactiveTableId.width/3 * 2
                }

                TableViewColumn
                {
                    role: "heartRate";
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
