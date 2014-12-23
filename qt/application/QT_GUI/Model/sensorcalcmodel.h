//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef SENSORCALCMODEL_H
#define SENSORCALCMODEL_H

#include <QAbstractListModel>
#include "Model/Data/calcsensordata.h"
#include "Model/sensormodel.h"
#include <QDebug>

class SensorCalcModel: public QAbstractListModel
{
    Q_OBJECT
    public:

        SensorCalcModel(SensorModel& aModel, QObject* aParent = 0);

        void setNewSensorCalcModel(const QList<CalcSensorData>& aSensorModel);

        /**
         * @brief updateCalcValues aktualisiert die Attribute, wenn sich die Daten ändern
         */
        void updateCalcValues(const SensorModel& aModel);

    protected:

        /**
         * @brief m_calcSensorList Liste mit den berechneten Werten
         */
        QList<CalcSensorData> m_calcSensorList;

        /**
         * @brief m_Model model with current data to calculate specil information
         */
        SensorModel& m_Model;
};

#endif // SENSORCALCMODEL_H
