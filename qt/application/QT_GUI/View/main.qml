import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import "."

ApplicationWindow
{
    id: rootWindow
    title: qsTr("HeartRate Manager")
    color: Style.windowBackgroundColor
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
            title: qsTr("Resting Heart rate")
            source: "qrc:/View/InactiveDiagramTab.qml"
        }

        Tab {
            id: activeDiagramTabID
            objectName: "diagramTabName"
            title: qsTr("Activity Heart rate")
            source: "qrc:/View/ActiveDiagramTab.qml"
        }

        /*style: TabViewStyle {
            frameOverlap: 1
            tabsAlignment: Qt.AlignHCenter

            tab: Rectangle {
                color: styleData.selected ? Style.tabViewSelectedTabBgColor : Style.tabViewTabBgColor
                border.color: Style.tabViewTabBorderColor
                implicitWidth: //Math.max(text.width + 4, 80)
                implicitHeight: 30
                radius: 1
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    font.weight: styleData.selected ? Font.DemiBold : Font.Normal
                    color: styleData.selected ? Style.tabViewSelectedTabFontColor : Style.tabViewTabFontColor
                }
            }

            tabBar: Rectangle {
                color: Style.tabViewTabBgColor
                CustomBorder: {

                }
            }

            frame: Rectangle { color: Style.tabViewTabBgColor }
        }*/
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { text: "No device connected!" }
        }
    }
}
