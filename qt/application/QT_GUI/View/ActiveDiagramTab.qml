import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0

Rectangle {

            width: 900
            height: 600
            color: "#a1a1ab"
            objectName:"test"

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

            CustomPlotItem
            {
                state: "INIT_DIAGRAMM"

                id: customPlot
                x: 20
                y: 45
                width: 540
                height: 498
                objectName: "activeDiagramName"

                onStateChanged: { updateDataAndGUI() }

                Component.onCompleted: initCustomPlot()
            }

            TableView {
                x: 574
                y: 45
                width: 300
                height: 498

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

                itemDelegate:
                Item {
                         Text{
                                color: "blue"
                                text: styleData.value
                         }

                }
            }
}
