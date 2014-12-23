//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotlinechart.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  Include all declarations from CustomPlotBarChart
  *
  */

#ifndef CUSTOMPLOTLINECHART_H
#define CUSTOMPLOTLINECHART_H

#include <QPainter>
#include <QtQuick>
#include "Thirdparty/qcustomplot.h"
#include "Model/sensormodel.h"
#include "Model/Data/sensordata.h"

/**
 * @brief The CustomPlotLineChart class Paint a line chart on view. This class in include in qml code
 *
 */
class CustomPlotLineChart: public QQuickPaintedItem
{
    Q_OBJECT

    public:

        /** A new define qml attribute to get the current data to diagram */
        Q_PROPERTY(SensorModel* data READ getData WRITE setData)

        /**
        * @brief setData SETTER-Method to set the data
        */
        void setData(SensorModel*);

        /**
        * @brief getData GETTER-Method to get the current data
        * @return current data of diagram
        */
        SensorModel* getData();

        /**
         * @brief CustomPlotLineChart Constructor to init attributes and parent class
         * @param aParent Pointer to QQuickItem parent class
         */
        CustomPlotLineChart(QQuickItem* aParent = 0);

        /**
         * @brief CustomPlotLineChart Copy-Constructor is not allowed
         * @param aOther    Reference to a other CustomPlotLineChart to init Object
         */
        CustomPlotLineChart(const CustomPlotLineChart& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        CustomPlotLineChart& operator= (const CustomPlotLineChart& aRhs) = delete;

        /**
         * @brief ~CustomPlotLineChart Destructor of class
         */
        virtual ~CustomPlotLineChart ();

        /**
         * @brief paint paint with the current data a diagram
         * @param aPainter QPainter object to paint diagram
         *
         * This function must be implement from developer
         */
        void paint(QPainter* aPainter);

        /**
         * @brief initCustomPlot Set range and size of diagram
         *
         * This function is called from view to init diagram
         */
        Q_INVOKABLE void initCustomPlot();

        /**
         * @brief updateDataAndGUI delete old diagram and repaint a new diagram
         *
         * This function is called from view to update diagram
         */
        Q_INVOKABLE void updateDataAndGUI();

    private:

        /**
         * @brief m_activeModel Pointer to activeModel to update diagram with current values
         */
        SensorModel* m_activeModel;

        /**
         * @brief m_CustomPlot Pointer to a object from third party class QCustomPlot
         */
        QCustomPlot*    m_CustomPlot;

        /**
         * @brief m_xAxis Vector with all values for x-Axis
         */
        QVector<double> m_xAxis;

        /**
         * @brief m_yAxis Vector with all values for y-Axis
         */
        QVector<double> m_yAxis;

        /**
         * @brief m_barChart Object with the current type of diagram
         */
        QCPLineEnding* m_lineChart;

        /**
         * @brief updateCustomPlotSize Update the size of the diagram
         */
        void updateCustomPlotSize();

        /**
         * @brief calculateData Calculate data from attached Model
         */
        void calculateData();
};

#endif // CUSTOMPLOTLINECHART_H
