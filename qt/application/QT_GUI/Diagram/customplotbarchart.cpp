//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotbarchart.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "customplotbarchart.h"
#include <QDebug>

void CustomPlotBarChart ::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    m_barChart = new QCPBars(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_CustomPlot->addPlottable(m_barChart);

    calculateData();

    m_barChart->setData(m_xAxis, m_yAxis);

    m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
    m_CustomPlot->yAxis->setRange(0, MAX_HEARTRATE);
    m_CustomPlot->xAxis->setLabel(tr("Time"));
    m_CustomPlot->yAxis->setLabel(tr("Heart Rate"));

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
                                                                m_barChart(0)


{
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
