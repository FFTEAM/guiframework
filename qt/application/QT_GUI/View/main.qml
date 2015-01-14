import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.0
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
    }

    TabView {

        id: tabviewId
        objectName: "TabViewName"
        anchors.fill: parent

        // Costumize tab view
        style: TabViewStyle {
            tabsAlignment: Qt.AlignLeft
            frameOverlap: 0
            frame: Rectangle { color: "whitesmoke";}

            tab: Rectangle {
                id: tabbarId
                color: styleData.selected ? "whitesmoke":"grey"
                implicitWidth: Math.max(text.width + 25, 100)
                implicitHeight: 25
                radius: 2

                // Add Icon to tab
                Image {
                    id: logoId
                    source: tabviewId.getTab(styleData.index).iconSource
                    height: parent.height - 5
                    width: tabbarId.implicitWidth - text.width - 12
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                }

                // Add text to tab
                Text {
                    id: text
                    text: styleData.title
                    height: parent.height
                    color: styleData.selected ? "black":"white"
                    verticalAlignment: Text.AlignVCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    renderType: Text.NativeRendering
               }
            }
        }

        IconTab {
            id: inactiveDiagramTabID
            objectName: "diagramTabName"
            title: qsTr("Resting Heart rate")
            source: "qrc:/View/InactiveDiagramTab.qml"
            iconSource: "qrc:/Images/standing_black.png"
        }

        IconTab {
            id: activeDiagramTabID
            objectName: "diagramTabName"
            title: qsTr("Activity Heart rate")
            source: "qrc:/View/ActiveDiagramTab.qml"
            iconSource: "qrc:/Images/running_black.png"
        }
    }
}
