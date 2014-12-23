//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensormodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   27.11.2014 17:50:00 GMT
  *
  * @brief  Include all declarations from SensorModel
  *
  */

#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/Data/sensordata.h"
#include <QDebug>

/**
 * @brief The SensorModel class This class represents a model for inactvie and active sensor data.
 *
 * The model is needed to update automatically view when the model data get change. This model is used in diagrams
 *
 */
class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    public:

        /** fried declaration to allow SensorCalcModel to acces on attributes in the class */
        friend class SensorCalcModel;

        /**
         * @brief The SensorRoles enum
         *
         * This enum store all Roles wich are needed for communcation with view
         */

        enum SensorRoles
        {
            SENSOR_DATE_ROLE,            /**< Role for time stamp */
            SENSOR_HEART_RATE_ROLE,      /**< Role for heart rate */
            SENSOR_STEP_LENGTH_ROLE      /**< Role for step length */
        };

        /**
         * @brief ~SensorModel Destructor is needed to declare a new QVariant type
         */
        ~SensorModel();

        /**
         * @brief SensorModel Constructor is needed to declare a new QVariant type
         */
        SensorModel();

        /**
         * @brief SensorModel Copy-Constructor is needed to declare a new QVariant type
         * @param aOther
         */
        SensorModel(const SensorModel& aOther);

        /**
         * @brief getDataList GETTER-Method for data list
         * @return
         */
        QList<const SensorData*> getDataList() const;

        /**
         * @brief addSensorData Add a new data object to model
         * @param aSensorData New data object
         */
        void addSensorData(const SensorData* aSensorData);

        /**
         * @brief setNewSensorModel Add a new list of data objects to model
         * @param aSensorModel List with new data objects
         */
        void setNewSensorModel(QList<const SensorData*>& aSensorModel);

        /**
         * @brief getSensorModelCount GETTER-Method for the size of the data list
         * @return Size of data list
         */
        int getSensorModelCount() const;

        /**
         * @brief getSingleSensorData GETTER-Method for a single data object
         * @param aIndex Index in model to find the data object
         * @return Selected data object
         */
        const SensorData* getSingleSensorData(const int aIndex) const;

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

    private:

        /**
         * @brief  cleanList clear sensorList and clean memory
         */
        void cleanList();

        /**
         * @brief m_sensorList QList with all data objects
         */
        QList<const SensorData*> m_sensorList;
};

#endif // SENSORMODEL_H
