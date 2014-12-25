//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   activesensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   16.12.2014 13:15:00 GMT
  *
  * @brief  Include all declarations from ActiveSensorCalcModel
  *
  */

#ifndef ACTIVESENSORCALCMODEL_H
#define ACTIVESENSORCALCMODEL_H

#include "Model/sensorcalcmodel.h"

/**
 * @brief The ActiveSensorCalcModel class This class represents a model for active calc values
 */
class ActiveSensorCalcModel: public SensorCalcModel
{
    public:

        /**
         * @brief ActiveSensorCalcModel Constructor to init all attributes
         * @param aModel Reference to a SensorModel to store all data to make some calculations
         */
        ActiveSensorCalcModel(SensorModel& aModel);

        /**
         * @brief The SensorCalcRoles enum Inlcude all roles from model
         */
        enum SensorCalcRoles
        {
            ACTIVE_SENSOR_CALC_VALUE_ROLE = 0,          /**< Role for a single active calc value */
            ACTIVE_SENSOR_CALC_DESCRIPTION_ROLE,        /**< Role for a single active calc description */
            ACTIVE_SENSOR_CALC_UNITOFMEASUREMENT_ROLE   /**< Role for a single active calc unit of measurement */
        };

        /**
         * @brief data Return to a index and role a QVariant value for view
         * @param aIndex Index of model
         * @param aRole Current Role
         * @return QVariant value with value and role
         *
         * This function is used by model/view on QT
         */
        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        /**
         * @brief rowCount Actual count of rows in model
         * @param aParent -
         * @return Count of rows in model
         *
         * This function is used by model/view on QT
         */
        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        /**
         * @brief updateCalcValues Update all calc values when data from model change
         */
        void updateCalcValues(const SensorModel& aModel);

    protected:

        /**
         * @brief roleNames Connect Roles on view with roles in model
         * @return QHash with the connected roles
         *
         * This function is used by model/view on QT
         */
        QHash<int, QByteArray> roleNames() const;

    private:

        /**
         * @brief m_Duration Calculate Duration from a single run (Activity measurement)
         */
        double m_Duration;
};

#endif // ACTIVESENSORCALCMODEL_H
