//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensormodel.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   27.11.2014 17:52:00 GMT
  *
  * @brief  Implementation file of SensorModel class
  *
  */

#include "sensormodel.h"

SensorModel::SensorModel() : QAbstractListModel(0)
{
    // C'tor
}

SensorModel::SensorModel(const SensorModel& aOther)
{
    m_sensorList = aOther.getDataList();
}

QList<const SensorData *> SensorModel::getDataList() const
{
    return m_sensorList;
}

SensorModel::~SensorModel()
{
    // cleaning up
    cleanList();
}

void SensorModel::cleanList()
{
    qDebug("cleaning up sensor data....");
    qint64 size = m_sensorList.count();
    beginResetModel();
    for (qint64 i = 0; i < size; i++)
    {
        delete m_sensorList.at(i);
        m_sensorList[i] = 0;
    }
    m_sensorList.clear();
    endResetModel();
}

void SensorModel::addSensorData(const SensorData* aSensorData)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_sensorList.append(aSensorData);
    endInsertRows();
}

void SensorModel::setNewSensorModel(QList<const SensorData*>& aSensorModel)
{
    beginResetModel();
    cleanList();
    m_sensorList = aSensorModel;
    endResetModel();
}

int SensorModel::getSensorModelCount() const
{
    return m_sensorList.count();
}

const SensorData* SensorModel::getSingleSensorData(const int aIndex) const
{
    if(aIndex >=0 && aIndex <= m_sensorList.size())
    {
        return m_sensorList.at(aIndex);
    }
    else
    {
        qDebug() << "Invalid Index";
        return 0;
    }
}

QVariant SensorModel::data(const QModelIndex &aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();
    const SensorData* sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        case SENSOR_HEART_RATE_ROLE:    return sensorData->getHeartRate(); break;

        case SENSOR_DATE_ROLE:          return sensorData->getDate(); break;

        case SENSOR_STEP_LENGTH_ROLE:   return sensorData->getStepLength(); break;

        default:                        return QVariant();
    }
}

int SensorModel::rowCount(const QModelIndex &aParent) const
{
    Q_UNUSED(aParent);
    return m_sensorList.count();
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[SENSOR_HEART_RATE_ROLE]   = "heartRate";
    roles[SENSOR_DATE_ROLE]         = "date";
    roles[SENSOR_STEP_LENGTH_ROLE]  = "stepLength";

    return roles;
}
