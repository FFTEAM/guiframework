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
            signal settingsActionIsTriggered();

            objectName: "settingsActionName"
            id: settingsActionID
            text: "&Settings"
            tooltip: "Set configuration"
            onTriggered: {
                var component = Qt.createComponent("qrc:/View/SettingsDialog.qml");
                var window = component.createObject(rootWindow);
                window.show;
            }
    }

    Action {
            id: saveActionID
            text: "&Save"
            shortcut: StandardKey.Save
            tooltip: "Save data to System"
    }

    Action {

            signal updateActionIsTriggered();

            objectName: "updateActionName"
            id: updateActionID
            text: "&Update Data"
            shortcut: StandardKey.Print
            tooltip: "Update data form Device"
            onTriggered: updateActionIsTriggered();
    }

    Action {

            signal printButtonIsPressed();

            objectName: "printActionName"
            id: printActionID
            text: "&Print"
            shortcut: StandardKey.Print
            tooltip: "Print data"
            onTriggered: printButtonIsPressed();
    }

    menuBar:
        MenuBar {
            id: menubarID
        Menu {
               title: qsTr("Data")
               MenuItem { text: qsTr("Settings"); action: settingsActionID }
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
