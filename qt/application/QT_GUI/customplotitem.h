#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H

#include "../../third_party/qcustomplot.h"
#include <QtQuick>
#include <QPainter>
#include <QColor>
#include <QVector>
#include "Model/sensormodel.h"

const int MAX_HEARTRATE = 230;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

    public:

        CustomPlotItem( QQuickItem* aParent = 0 );
        virtual ~CustomPlotItem();

        Q_INVOKABLE void initCustomPlot();
        Q_INVOKABLE void updateDataAndGUI();

        void paint(QPainter* aPainter);

    private:

        QCustomPlot*    m_CustomPlot;
        QVector<double> m_xAxis;
        QVector<double> m_yAxis;
        QCPBars* m_gantChart;

        void updateCustomPlotSize();
        void calculateData();

};

#endif // CUSTOMPLOTITEM_H
