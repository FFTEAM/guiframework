//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   inactivesensorcalcmodel.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "inactivesensorcalcmodel.h"

InactiveSensorCalcModel::InactiveSensorCalcModel(SensorModel& aModel) : SensorCalcModel(aModel,0)
{
    updateCalcValues(aModel);
}

QVariant InactiveSensorCalcModel::data(const QModelIndex &aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_calcSensorList.count()) return QVariant();
    const CalcSensorData& calcSensorData = m_calcSensorList[aIndex.row()];

    switch(aRole)
    {
        case INACTIVE_SENSOR_CALC_VALUE_ROLE:       return calcSensorData.getCalcValue(); break;

        case INACTIVE_SENSOR_CALC_DESCRIPTION_ROLE: return calcSensorData.getDescription(); break;

        default:                                    return QVariant();
    }
}

int InactiveSensorCalcModel::rowCount(const QModelIndex &aParent) const
{
    Q_UNUSED(aParent);
    return m_calcSensorList.count();
}

QHash<int, QByteArray> InactiveSensorCalcModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[INACTIVE_SENSOR_CALC_VALUE_ROLE]          = "inactiveCalcValue";
    roles[INACTIVE_SENSOR_CALC_DESCRIPTION_ROLE]    = "inactiveCalcDescription";

    return roles;
}
