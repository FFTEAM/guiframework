//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotlinechart.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "customplotlinechart.h"

void CustomPlotLineChart::setData(SensorModel* aModel)
{
    m_activeModel = aModel;
}

SensorModel *CustomPlotLineChart::getData()
{
    return m_activeModel;
}

CustomPlotLineChart::CustomPlotLineChart(QQuickItem* aParent):  QQuickPaintedItem(aParent),
                                                                m_activeModel(0),
                                                                m_CustomPlot(0),
                                                                m_xAxis(0),
                                                                m_yAxis(0),
                                                                m_lineChart(0)

{
    qDebug() << "Constructor called";
    // add connection for resizing the chart:
    connect(this, &QQuickPaintedItem::widthChanged, this, &CustomPlotLineChart::updateCustomPlotSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &CustomPlotLineChart::updateCustomPlotSize);
}

CustomPlotLineChart::~CustomPlotLineChart()
{
    delete m_CustomPlot;
    m_CustomPlot    = 0;
}

void CustomPlotLineChart::paint(QPainter* aPainter)
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );
        aPainter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotLineChart::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    m_CustomPlot->addGraph();

    calculateData();

    m_CustomPlot->graph(0)->setData(m_xAxis, m_yAxis);
    m_CustomPlot->yAxis->setRange(0, 230);
    m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
    m_CustomPlot->xAxis->setLabel(tr("Time"));
    m_CustomPlot->yAxis->setLabel(tr("Heart Rate"));

    updateCustomPlotSize();

    qDebug() << "initCustomPlot()";
}

void CustomPlotLineChart::updateDataAndGUI()
{
    if(m_CustomPlot)
    {
        m_CustomPlot->clearGraphs();
        m_CustomPlot->addGraph();

        calculateData();

        m_CustomPlot->graph(0)->setData(m_xAxis, m_yAxis);
        m_CustomPlot->xAxis->setRange(0, m_xAxis.size() + 1);
        m_CustomPlot->yAxis->setRange(0, 230);

        update();
    }
}

void CustomPlotLineChart::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}

void CustomPlotLineChart::calculateData()
{
    qDebug() << "calculateData called";
    if(m_xAxis.size() != 0) m_xAxis.clear();
    if(m_yAxis.size() != 0) m_yAxis.clear();

    if(m_activeModel != 0)
    {
        const int length = m_activeModel->getSensorModelCount();
        double time = 1.0;

        for(int index = 0; index < length; index++)
        {
            m_xAxis.append(time);
            const SensorData* data = m_activeModel->getSingleSensorData(index);
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
