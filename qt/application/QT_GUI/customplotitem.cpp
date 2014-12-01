#include "CustomPlotItem.h"
#include <QDebug>

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    QCPBars *newBars = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_CustomPlot->addPlottable(newBars);

    // Generate Data
    QVector<double> xData;
    xData.append(1.0);
    xData.append(2.0);
    xData.append(3.0);
    xData.append(4.0);

    QVector<double> yData;
    yData.append(5.0);
    yData.append(2.0);
    yData.append(10.0);
    yData.append(3.0);

    newBars->setName("Country population");
    newBars->setData(xData, yData);

    m_CustomPlot->xAxis->setRange(0,10);
    m_CustomPlot->yAxis->setRange(0,15);
    m_CustomPlot->xAxis->setLabel(tr("Time"));
    m_CustomPlot->yAxis->setLabel(tr("Heart Rate"));

    updateCustomPlotSize();

    qDebug() << "initCustomPlot()";
}

CustomPlotItem::CustomPlotItem(QQuickItem* aParent) : QQuickPaintedItem(aParent) , m_CustomPlot(0)
{
    // C'tor
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = 0;
}

void CustomPlotItem::paint(QPainter* aPainter)
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );
        aPainter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}
