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

#include "sensormodel.h"

SensorModel::SensorModel(QObject* aParent) : QAbstractListModel(aParent)
{
    // C'tor
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

void SensorModel::setNewSensorModel(const QList<const SensorData*>& aSensorModel)
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
