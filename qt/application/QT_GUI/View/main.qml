import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle
{
    width: 700
    height: 500
    color: "#fbd5ba"
    id: mainRectacleID
    objectName: "mainRectacleName"

    TabView {

        id: tableviewID
        objectName: "TabViewName"
        width: 600;
        height: 400;
        x: 50;
        y: 50;

        Tab {
            id: deviceTabID
            objectName:  "deviceTabName"
            title: qsTr("Device")
            source: "qrc:/View/DeviceTab.qml"
        }

        Tab {
            id: tableTabID
            objectName: "tableTabName"
            title: qsTr("Table Data")
            source: "qrc:/View/TableDataTab.qml"
        }

        Tab {
            id: diagramTabID
            objectName: "diagramTabName"
            title: qsTr("Diagram")
            source: "qrc:/View/DiagramTab.qml"
        }

        Tab
        {
            id: detailDataTabID
            objectName: "detailDataTabName"
            title: qsTr("Detail Data")
            source: "qrc:/View/DetailDataTab.qml"
        }
     }
}
