import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0

Rectangle {

            width: 600;
            height: 400;

            CustomPlotItem
            {
                width: 200
                height: 200
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                id: customPlot
            }
}
