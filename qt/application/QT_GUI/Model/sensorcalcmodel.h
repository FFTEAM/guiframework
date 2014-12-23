//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   15.12.2014 21:50:00 GMT
  *
  * @brief  Include all declarations from SensorCalcModel
  *
  */

#ifndef SENSORCALCMODEL_H
#define SENSORCALCMODEL_H

#include <QAbstractListModel>
#include "Model/Data/calcsensordata.h"
#include "Model/sensormodel.h"
#include <QDebug>

/**
 * @brief The SensorCalcModel class This class represents a model for calculate data to show on view
 *
 *  This is the parent class of InactiveSensorCalcModel and ActiveSensorCalcModel. Duplicated code from
 *  both sub classes is abstract to this class
 *
 */
class SensorCalcModel: public QAbstractListModel
{
    Q_OBJECT
    public:

        /**
         * @brief SensorCalcModel Constructor to init all attributes on class
         * @param aModel    Reference to a SensorModel with inactvie or active sensor data
         * @param aParent   Pointer to QAbstractLisModel parent class
         */
        SensorCalcModel(SensorModel& aModel, QObject* aParent = 0);

        /**
         * @brief setNewSensorCalcModel Add a new sensor data list with calculate values to model
         * @param aSensorModel
         */
        void setNewSensorCalcModel(const QList<CalcSensorData>& aSensorModel);

        /**
         * @brief updateCalcValues Update all calc values when data from model change
         */
        void updateCalcValues(const SensorModel& aModel);

    protected:

        /**
         * @brief m_calcSensorList QList with sensor data objects (Data from Model)
         */
        QList<CalcSensorData> m_calcSensorList;

        /**
         * @brief m_Model Reference from SensorModel to calculate data
         */
        SensorModel& m_Model;
};

#endif // SENSORCALCMODEL_H
