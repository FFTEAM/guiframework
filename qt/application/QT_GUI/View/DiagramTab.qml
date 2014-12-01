import QtQuick 2.0
import QtQuick.Controls 1.2
import CostumPlot 1.0

Rectangle {

            width: 600;
            height: 400;
            color: "#a1a1ab"

            CustomPlotItem
            {
                width: 350
                height: 350
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                id: customPlot

                Component.onCompleted: initCustomPlot()
            }
}
