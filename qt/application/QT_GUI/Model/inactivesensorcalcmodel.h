//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   inactivesensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief Include all declarations from InactiveSensorCalcModel
  *
  */

#ifndef INACTIVESENSORCALCMODEL_H
#define INACTIVESENSORCALCMODEL_H

#include "Model/sensorcalcmodel.h"

/**
 * @brief The InactiveSensorCalcModel class This class represents a model for inactive calc values
 */
class InactiveSensorCalcModel : public SensorCalcModel
{
    public:

        /**
         * @brief InactiveSensorCalcModel Constructor to init all attributes
         * @param aModel Reference to a SensorModel to calculate data
         */
        InactiveSensorCalcModel(SensorModel& aModel);

        /**
         * @brief The SensorCalcRoles enum Inlcude all roles from model
         */
        enum SensorCalcRoles
        {
            INACTIVE_SENSOR_CALC_VALUE_ROLE = 0,    /**< Role for a single inactive calc value */
            INACTIVE_SENSOR_CALC_DESCRIPTION_ROLE   /**< Role for a single inactive calc description */
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

        protected:

        /**
         * @brief roleNames Connect Roles on view with roles in model
         * @return QHash with the connected roles
         *
         * This function is used by model/view on QT
         */
        QHash<int, QByteArray> roleNames() const;
};

#endif // INACTIVESENSORCALCMODEL_H
