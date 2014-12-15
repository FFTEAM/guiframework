import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    color: "#f3f3f3"
    radius: 3
    border.color: "#d1d1d1"
    border.width: 1
    anchors.fill: parent
    anchors.topMargin: 10
    anchors.bottomMargin: 10
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    state: "NO_DEVICE_CONNECT"

    states:[

        State
        {
            name: "NO_DEVICE_CONNECT"
            PropertyChanges { target: deviceTabID; enabled: true; focus: true}
            PropertyChanges { target: tableTabID; enabled: false}
            PropertyChanges { target: diagramTabID; enabled: false}
            PropertyChanges { target: detailDataTabID; enabled: false}
            PropertyChanges { target: importButtonID; enabled: false}
            PropertyChanges { target: connectionButtonID; text: qsTr("connect")}
            PropertyChanges { target: searchDeviceButtonID; enabled: true}
        },

        State
        {
            name: "DEVICE_CONNECT"
            PropertyChanges { target: tableTabID; enabled: true}
            PropertyChanges { target: diagramTabID; enabled: true ; focus: true}
            PropertyChanges { target: detailDataTabID; enabled: true}
            PropertyChanges { target: importButtonID; enabled: true}
            PropertyChanges { target: connectionButtonID; text: qsTr("disconnect")}
            PropertyChanges { target: searchDeviceButtonID; enabled: false}
        }]

    Component {
              id: highlightBar
              Rectangle {
                  width: 408; height: 30
                  radius: 5
                  color: "lightsteelblue"
                  y: listView.currentItem.y;
                  x: listView.currentItem.x-3;
                  Behavior on y { PropertyAnimation {} }
              }
    }

    Component {
        id: listDelegate
        Item {
            width: 400; height: 30
            Row {
                 spacing: 2
                 width: 400
                 Image {
                        id: itemBtn
                        source: "qrc:/Images/bluetooth_icon.png"
                        anchors.verticalCenter: parent.verticalCenter
                        height: 30;
                        width: 30;

                        MouseArea {
                            anchors.fill: parent;
                            onClicked:{
                                 listView.currentIndex = index;
                            }
                        }
                 }

                 Text {
                     text: deviceName;
                     anchors.verticalCenter: parent.verticalCenter
                     width: 340
                     MouseArea {
                         anchors.fill: parent;
                         onClicked:{

                              listView.currentIndex = index;
                         }
                     }
                 }

                 Image {
                     id: connectionState
                     source: colorState;
                     anchors.verticalCenter: parent.verticalCenter
                     width: 30
                     height:30
                     MouseArea {
                         anchors.fill: parent;
                         onClicked:{
                              listView.currentIndex = index;
                         }
                     }
                 }
            }
        }
    }


    ListView {
        id: listView
        objectName: "listViewName"
        anchors.rightMargin: 101
        anchors.bottomMargin: 87
        anchors.leftMargin: 101
        width: 500
        anchors.top: parent.top
        anchors.topMargin: 65
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        snapMode: ListView.SnapOneItem
        layoutDirection: Qt.RightToLeft
        boundsBehavior: Flickable.DragOverBounds
        contentHeight: 100
        anchors.margins: 5
        model: deviceModel
        delegate: listDelegate
        highlight: highlightBar
        highlightFollowsCurrentItem: false
        focus: true

        BorderImage {
            id: listviewBorderID
            x: -50
            source: "qrc:/Images/listview_border.png"
            width: 498; anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -33
            anchors.top: parent.top
            anchors.topMargin: -35
            border.left: 1; border.top: 1
            border.right: 1; border.bottom: 1
        }
    }

    Button {
        id: searchDeviceButtonID
        objectName: "searchDeviceButton"
        signal searchDeviceButtonIsPressed();
        x: 394
        y: 254
        height: 30
        width: 105
        text: qsTr("search device")
        anchors.right: parent.right
        anchors.rightMargin: 101
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16

        onClicked:
        {
            searchDeviceButtonIsPressed();
        }
    }

    Button {
        id: connectionButtonID
        objectName: "connectionButton"
        signal connectionButtonIsPressed(int index);
        x: 249
        y: 254
        height: 30
        anchors.horizontalCenterOffset: 0
        width: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16

        onClicked: {
            tmp.state == 'NO_DEVICE_CONNECT' ? tmp.state = "DEVICE_CONNECT" : tmp.state = 'NO_DEVICE_CONNECT'
            connectionButtonIsPressed(listView.currentIndex);
        }
    }

    Button {
        id: importButtonID
        objectName: "importButton"
        signal importButtonIsPressed();
        y: 254
        width: 94
        height: 30
        text: qsTr("import data")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 101

        onClicked: {

            importButtonIsPressed();
        }
    }
}
