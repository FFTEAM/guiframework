#ifndef CUSTOMPLOTBARCHART_H
#define CUSTOMPLOTBARCHARTM_H

#include "../../third_party/qcustomplot.h"
#include <QtQuick>
#include <QPainter>
#include <QColor>
#include <QVector>
#include "Model/sensormodel.h"

const int MAX_HEARTRATE = 230;

class CustomPlotBarChart : public QQuickPaintedItem
{
    Q_OBJECT

    public:

        CustomPlotBarChart (QQuickItem* aParent = 0);
        virtual ~CustomPlotBarChart ();

        Q_INVOKABLE void initCustomPlot();
        Q_INVOKABLE void updateDataAndGUI();

        void paint(QPainter* aPainter);

    private:

        QCustomPlot*    m_CustomPlot;
        QVector<double> m_xAxis;
        QVector<double> m_yAxis;
        QCPBars* m_barChart;

        void updateCustomPlotSize();
        void calculateData();

};

#endif // CUSTOMPLOTBARCHART_H
