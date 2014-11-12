import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Rectangle
{
    visible: true
    width: 360
    height: 360

    Text
    {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
