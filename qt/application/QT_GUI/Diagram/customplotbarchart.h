//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotbarchart.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   15.12.2014 18:45:00 GMT
  *
  * @brief  Include all declarations from CustomPlotBarChart
  *
  */

#ifndef CUSTOMPLOTBARCHART_H
#define CUSTOMPLOTBARCHARTM_H

#include "Thirdparty/qcustomplot.h"
#include "Model/sensormodel.h"
#include <QtQuick>
#include <QPainter>
#include <QColor>
#include <QVector>

/** Fix attribute for heart rate */
const int MAX_HEARTRATE = 230;

/**
 * @brief The CustomPlotBarChart class Paint a bar chart on view. This class in include in qml code
 *
 */
class CustomPlotBarChart : public QQuickPaintedItem
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
         * @brief CustomPlotBarChart Constructor to init attributes and parent class
         * @param aParent Pointer to QQuickItem parent class
         */
        CustomPlotBarChart (QQuickItem* aParent = 0);


        /**
         * @brief CustomPlotBarChart Copy-Constructor is not allowed
         * @param aOther    Reference to a other CustomPlotBarChart to init Object
         */
        CustomPlotBarChart(const CustomPlotBarChart& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        CustomPlotBarChart& operator= (const CustomPlotBarChart& aRhs) = delete;

        /**
         * @brief ~CustomPlotBarChart Destructor of class
         */
        virtual ~CustomPlotBarChart ();

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

        /**
         * @brief paint paint with the current data a diagram
         * @param aPainter QPainter object to paint diagram
         *
         * This function must be implement from developer
         */
        void paint(QPainter* aPainter);

    private:

        /**
         * @brief m_inactiveModel Pointer to inactiveModel to update diagram with current values
         */
        SensorModel* m_inactiveModel;

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
        QCPBars* m_barChart;

        /**
         * @brief textLabel Label for a overview text
         */
        QCPItemText *textLabel;

        /**
         * @brief m_tickValueVector Vector for additional informations on x-Axis
         */
        QVector<double> m_tickValueVector;

        /**
         * @brief m_tickLabelVector Vector with lables for additional informations on x-Axis
         */
        QVector<QString> m_tickLabelVector;

        /**
         * @brief updateCustomPlotSize Update the size of the diagram
         */
        void updateCustomPlotSize();

        /**
         * @brief calculateData Calculate data from attached Model
         */
        void calculateData();

        /**
         * @brief calculateTicksAndLabels Calculate additional informations for x-Axis
         */
        void calculateTicksAndLabels();
};

#endif // CUSTOMPLOTBARCHART_H
