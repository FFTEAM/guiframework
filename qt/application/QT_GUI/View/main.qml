import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

ApplicationWindow
{
    id: rootWindow
    visible: true
    width: 900
    height: 600

    Action {
            id: saveActionID
            text: qsTr("&Save")
            shortcut: StandardKey.Save
            tooltip: qsTr("Save data to System")
    }

    Action {

            signal updateActionIsTriggered();

            objectName: "updateActionName"
            id: updateActionID
            text: qsTr("&Update Data")
            shortcut: StandardKey.Print
            tooltip: qsTr("Update data form Device")
            onTriggered: updateActionIsTriggered();
    }

    Action {

            signal printActionIsTriggered();

            objectName: "printActionName"
            id: printActionID
            text: qsTr("&Print")
            shortcut: StandardKey.Print
            tooltip: qsTr("Print data")
            onTriggered: printActionIsTriggered();
    }

    menuBar:
    MenuBar {
                id: menubarID
        Menu {
           title: qsTr("Data")
           MenuItem { text: qsTr("Save"); action: saveActionID }
           MenuItem { text: qsTr("Print"); action: printActionID }
           MenuItem { text: qsTr("Update Data"); action: updateActionID }
        }

    }

    TabView {

            id: tableviewID
            objectName: "TabViewName"
            width: parent.width;
            height: parent.height

            Tab {
                id: inactiveDiagramTabID
                objectName: "diagramTabName"
                title: qsTr("Inactive Heartrate")
                source: "qrc:/View/InactiveDiagramTab.qml"
            }

            Tab {
                id: activeDiagramTabID
                objectName: "diagramTabName"
                title: qsTr("Active Heartrate")
                source: "qrc:/View/ActiveDiagramTab.qml"
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
