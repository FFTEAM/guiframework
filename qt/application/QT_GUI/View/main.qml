import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

ApplicationWindow
{
    id: rootWindow
    title: qsTr("HeartRate Manager")
    color: "#ffffff"
    visible: true
    visibility: "Maximized"
    minimumWidth: 800
    minimumHeight: 600

    Action {
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

    menuBar: MenuBar {
        id: menubarID
        Menu {
               title: qsTr("File")

               MenuItem { text: qsTr("Settings"); action: settingsActionID }
               MenuSeparator {}
               MenuItem { text: qsTr("Save"); action: saveActionID }
               MenuItem { text: qsTr("Print"); action: printActionID }
               MenuItem { text: qsTr("Update Data"); action: updateActionID }
               MenuSeparator {}
               MenuItem { text: qsTr("Exit"); onTriggered: Qt.quit() }
        }

        Menu {
               title: qsTr("?")
               MenuItem { text: qsTr("About"); onTriggered: Qt.quit() }
        }
    }

    TabView {
        id: tableviewID
        objectName: "TabViewName"
        anchors.fill: parent

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

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { text: "No device connected!" }
        }
    }
}
