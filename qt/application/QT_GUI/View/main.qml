import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import "."

ApplicationWindow
{
    id: rootWindow
    title: qsTr("HeartRate2Go")
    color: Style.windowBackgroundColor
    visible: true
    visibility: "Maximized"
    minimumWidth: 975
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

               MenuItem { text: qsTr("Print"); action: printActionID }
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

        IconTab {
            id: inactiveDiagramTabID
            objectName: "diagramTabName"
            title: qsTr("Resting Heart rate")
            iconSource: "qrc:/Images/standing_black.png"
            source: "qrc:/View/InactiveDiagramTab.qml"
        }

        IconTab {
            id: activeDiagramTabID
            objectName: "diagramTabName"
            title: qsTr("Activity Heart rate")
            iconSource: "qrc:/Images/running_black.png"
            source: "qrc:/View/ActiveDiagramTab.qml"
        }
    }

    /*statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label {
                text: "No device connected!"
                renderType: Text.NativeRendering
            }
        }
    }*/
}
