//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotbarchart.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   15.12.2014 18:46:00 GMT
  *
  * @brief  Implementation file of CustomPlotBarChart class
  *
  */

#include "customplotbarchart.h"
#include <QDebug>

void CustomPlotBarChart ::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();
    QCPItemText *textLabel = new QCPItemText(m_CustomPlot);
    m_CustomPlot->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Text Item Demo");
    textLabel->setPen(QPen(Qt::black)); // show black border around text

    m_barChart = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_CustomPlot->addPlottable(m_barChart);

    calculateData();
    calculateTicksAndLabels();

    m_barChart->setData(m_xAxis, m_yAxis);

    m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
    m_CustomPlot->yAxis->setRange(0, MAX_HEARTRATE);
    m_CustomPlot->xAxis->setLabel(tr("Time"));
    m_CustomPlot->yAxis->setLabel(tr("Heart Rate"));

    m_CustomPlot->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

    m_CustomPlot->xAxis->setAutoTickLabels(false);
    m_CustomPlot->xAxis->setAutoTicks(false);
    m_CustomPlot->xAxis->setTickLabelRotation(45);

    updateCustomPlotSize();

    qDebug() << "initCustomPlot()";
}

void CustomPlotBarChart::setData(SensorModel* aModel)
{
    qDebug() << "setData called";
    m_inactiveModel = aModel;
}

SensorModel* CustomPlotBarChart::getData()
{
    return m_inactiveModel;
}

CustomPlotBarChart ::CustomPlotBarChart (QQuickItem* aParent) : QQuickPaintedItem(aParent),
                                                                m_inactiveModel(0),
                                                                m_CustomPlot(0),
                                                                m_xAxis(0),
                                                                m_yAxis(0),
                                                                m_barChart(0),
                                                                m_tickValueVector(0),
                                                                m_tickLabelVector(0)


{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );
    // add connection for resizing the chart:
    connect(this, &QQuickPaintedItem::widthChanged, this, &CustomPlotBarChart::updateCustomPlotSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &CustomPlotBarChart::updateCustomPlotSize);
}

CustomPlotBarChart::~CustomPlotBarChart()
{
    delete m_CustomPlot;
    m_CustomPlot    = 0;
}

void CustomPlotBarChart::paint(QPainter* aPainter)
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );
        aPainter->drawPixmap( QPoint(), picture );
    }
}

/*void CustomPlotBarChart::hoverMoveEvent(QHoverEvent * event)
{
    qDebug() << Q_FUNC_INFO;
    int x = m_CustomPlot->xAxis->pixelToCoord(event->pos().x());
    int y = m_CustomPlot->yAxis->pixelToCoord(event->pos().y());

    //textLabel->setText("Test");
    //m_CustomPlot->setToolTip(QString("%1 , %2").arg(x).arg(y));
}*/

void CustomPlotBarChart::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}

void CustomPlotBarChart::updateDataAndGUI()
{
    if(m_CustomPlot)
    {
        m_CustomPlot->clearPlottables();
        m_barChart = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
        m_CustomPlot->addPlottable(m_barChart);

        calculateData();
        calculateTicksAndLabels();

        m_barChart->setData(m_xAxis, m_yAxis);
        m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
        m_CustomPlot->yAxis->setRange(0, MAX_HEARTRATE);

        update();
    }
}

void CustomPlotBarChart::calculateData()
{
    qDebug() << "calculateData called xyc";
    if(m_xAxis.size() > 0) m_xAxis.clear();
    if(m_yAxis.size() > 0) m_yAxis.clear();

    if(m_inactiveModel != 0)
    {
        const int length = m_inactiveModel->getSensorModelCount();
        double time = 1.0;

        for(int index = 0; index < length; index++)
        {
            m_xAxis.append(time);
            const SensorData* data = m_inactiveModel->getSingleSensorData(index);
            if(data != 0)
            {
                m_yAxis.append(data->getHeartRate());
                time = time + 1;
            }
            else
            {
                qDebug() << "y axis value not found";
            }
        }
    }
    else
    {
        qDebug() << "Model not set";
    }
}

void CustomPlotBarChart::calculateTicksAndLabels()
{
    if(m_tickValueVector.size() != 0) m_tickValueVector.clear();
    if(m_tickLabelVector.size() != 0) m_tickValueVector.clear();

    if(m_inactiveModel != 0)
    {
        double time = 1.0;
        const int length = m_inactiveModel->getSensorModelCount();
        for(int i = 0; i<length; i++)
        {
            const SensorData* data = m_inactiveModel->getSingleSensorData(i);
            QDate date(data->getDate().date());
            m_tickLabelVector.append(date.toString("dd.MM.yyyy"));
            m_tickValueVector.append(time);
            time = time + 1;
        }

        m_CustomPlot->xAxis->setTickVector(m_tickValueVector);
        m_CustomPlot->xAxis->setTickVectorLabels(m_tickLabelVector);
    }
}
