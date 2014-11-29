#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H

#include "../../third_party/qcustomplot.h"
#include <QtQuick>
#include <QPainter>
#include <QColor>

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

    public:

        CustomPlotItem( QQuickItem* parent = 0 );
        virtual ~CustomPlotItem();

        Q_INVOKABLE void initCustomPlot();
        void paint( QPainter* painter );


    protected:

        void setupQuadraticDemo( QCustomPlot* customPlot );

    private:

        QCustomPlot*         m_CustomPlot;
        void updateCustomPlotSize();
};

#endif // CUSTOMPLOTITEM_H
