#include "CustomPlotItem.h"
#include <QDebug>

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    m_gantChart = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_CustomPlot->addPlottable(m_gantChart);

    calculateData();

    m_gantChart->setData(m_xAxis, m_yAxis);

    m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
    m_CustomPlot->yAxis->setRange(0, MAX_HEARTRATE);
    m_CustomPlot->xAxis->setLabel(tr("Time"));
    m_CustomPlot->yAxis->setLabel(tr("Heart Rate"));

    updateCustomPlotSize();

    qDebug() << "initCustomPlot()";
}

CustomPlotItem::CustomPlotItem(QQuickItem* aParent) : QQuickPaintedItem(aParent),
                                                      m_CustomPlot(0),
                                                      m_xAxis(0),
                                                      m_yAxis(0)

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
    qDebug() << "Call paint";
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

void CustomPlotItem::updateDataAndGUI()
{
    if(m_CustomPlot)
    {
        m_CustomPlot->clearPlottables();
        m_gantChart = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
        m_CustomPlot->addPlottable(m_gantChart);

        calculateData();

        m_gantChart->setData(m_xAxis, m_yAxis);
        update();
    }
}

void CustomPlotItem::calculateData()
{
    qDebug() << "calculateData called";
    if(m_xAxis.size() != 0) m_xAxis.clear();
    if(m_yAxis.size() != 0) m_yAxis.clear();

    const SensorModel& model = SensorModel::getInstance();
    const int length = model.getSensorModelCount();
    double time = 1.0;

    for(int index = 0; index < length; index++)
    {
        m_xAxis.append(time);
        const SensorData* data = model.getSingleSensorData(index);
        if(data != 0)
        {
            m_yAxis.append(data->getHeartRate().toInt());
            time = time + 1;
        }
        else
        {
            qDebug() << "y axis value not found";
        }
    }
}
