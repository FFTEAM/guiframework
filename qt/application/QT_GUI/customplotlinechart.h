#ifndef CUSTOMPLOTLINECHART_H
#define CUSTOMPLOTLINECHART_H

#include <QPainter>
#include <QtQuick>
#include "../../third_party/qcustomplot.h"
#include "Model/sensormodel.h"
#include "Model/sensordata.h"

class CustomPlotLineChart: public QQuickPaintedItem
{
    Q_OBJECT

    public:

        CustomPlotLineChart(QQuickItem* aParent = 0);
        virtual ~CustomPlotLineChart ();

        void paint(QPainter* aPainter);

        Q_INVOKABLE void initCustomPlot();
        Q_INVOKABLE void updateDataAndGUI();

    private:

        CustomPlotLineChart(const CustomPlotLineChart& aOther);
        CustomPlotLineChart& operator= (const CustomPlotLineChart& aRhs);

        QCustomPlot*    m_CustomPlot;
        QVector<double> m_xAxis;
        QVector<double> m_yAxis;
        QCPLineEnding* m_lineChart;

        void updateCustomPlotSize();
        void calculateData();
};

#endif // CUSTOMPLOTLINECHART_H
