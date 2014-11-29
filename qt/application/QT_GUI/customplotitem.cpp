#include "CustomPlotItem.h"
#include <QDebug>

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    qDebug() << "initCustomPlot()";
}

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent ) , m_CustomPlot( 0 )
{
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = 0;
}

void CustomPlotItem::paint(QPainter *painter)
{
    //QPen pen(QBrush(QColor("red")), 5);
    //painter->setPen(pen);
    //painter->setRenderHints(QPainter::Antialiasing, true);
    //painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);

    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );
        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::setupQuadraticDemo(QCustomPlot *customPlot)
{
    // make top right axes clones of bottom left axes:
        QCPAxisRect* axisRect = customPlot->axisRect();

        // generate some data:
        QVector<double> x( 101 ), y( 101 );   // initialize with entries 0..100
        QVector<double> lx( 101 ), ly( 101 ); // initialize with entries 0..100
        for (int i = 0; i < 101; ++i)
        {
            x[i] = i / 50.0 - 1;              // x goes from -1 to 1
            y[i] = x[i] * x[i];               // let's plot a quadratic function

            lx[i] = i / 50.0 - 1;             //
            ly[i] = lx[i];                    // linear
        }
        // create graph and assign data to it:
        customPlot->addGraph();
        customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
        customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
        customPlot->graph( 0 )->setData( x, y );

        customPlot->addGraph();
        customPlot->graph( 1 )->setPen( QPen( Qt::magenta ) );
        customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
        customPlot->graph( 1 )->setData( lx, ly );

        // give the axes some labels:
        customPlot->xAxis->setLabel( "x" );
        customPlot->yAxis->setLabel( "y" );
        // set axes ranges, so we see all data:
        customPlot->xAxis->setRange( -1, 1 );
        customPlot->yAxis->setRange( -1, 1 );

        customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}
