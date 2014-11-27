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

    void paint( QPainter* painter );


protected:


private:
    QCustomPlot*         m_CustomPlot;
};

#endif // CUSTOMPLOTITEM_H
