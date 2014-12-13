#include "sensormodel.h"

SensorModel::SensorModel(QObject* aParent) : QAbstractListModel(aParent)
{
    // C'tor
}

SensorModel &SensorModel::getInstance(const SensorDataType aType)
{
    static SensorModel activeInstance;
    static SensorModel inactiveInstance;

    if(aType == ACTIVE_SENSOR_DATA) return activeInstance;
    else return inactiveInstance;
}

QVariant SensorModel::data(const QModelIndex& aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();

    const SensorData& sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        case ACTIVE_SENSOR_HEART_RATE_ROLE:
        case INACTIVE_SENSOR_HEART_RATE_ROLE:    return sensorData.getHeartRate(); break;

        case ACTIVE_SENSOR_DATE_ROLE:
        case INACTIVE_SENSOR_DATE_ROLE:          return sensorData.getDate(); break;

        case ACTIVE_SENSOR_STEP_LENGTH:
        case INACTIVE_SENSOR_STEP_LENGTH:        return sensorData.getStepLength(); break;

        default:                                 return QVariant();
    }
}

int SensorModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);
    return m_sensorList.count();
}

void SensorModel::addSensorData(const SensorData& aSensorData)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_sensorList.append(aSensorData);
    endInsertRows();
}

void SensorModel::setNewSensorModel(const QList<SensorData>& aSensorModel)
{
    beginResetModel();
    m_sensorList = aSensorModel;
    endResetModel();
}
//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensormodel.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 14:12:00 GMT
  *
  * @brief Diese CPP-Datei enthält alle Implementierung der Methoden der Klasse SensorModel
  *
  */

int SensorModel::getSensorModelCount() const
{
    return m_sensorList.count();
}

const SensorData* SensorModel::getSingleSensorData(const int aIndex) const
{
    if(aIndex >=0 && aIndex <= m_sensorList.size())
    {
        return &m_sensorList.at(aIndex);
    }
    else
    {
        qDebug() << "Invalid Index";
        return 0;
    }
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ACTIVE_SENSOR_HEART_RATE_ROLE]    = "activeHeartRate";
    roles[ACTIVE_SENSOR_DATE_ROLE]          = "activeDate";
    roles[ACTIVE_SENSOR_STEP_LENGTH]        = "activeStepLength";
    roles[INACTIVE_SENSOR_HEART_RATE_ROLE]  = "inactiveHeartRate";
    roles[INACTIVE_SENSOR_DATE_ROLE]        = "inactiveDate";
    roles[INACTIVE_SENSOR_STEP_LENGTH]      = "inactiveStepLength";

    return roles;
}
