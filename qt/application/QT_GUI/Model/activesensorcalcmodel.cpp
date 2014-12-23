//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   activesensorcalcmodel.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  TImplementation file of ActiveSensorCalcModel class
  *
  */

#include "activesensorcalcmodel.h"

ActiveSensorCalcModel::ActiveSensorCalcModel(SensorModel& aModel): SensorCalcModel(aModel,0)
{
    updateCalcValues(m_Model);
}

QVariant ActiveSensorCalcModel::data(const QModelIndex& aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_calcSensorList.count()) return QVariant();
    const CalcSensorData& calcSensorData = m_calcSensorList[aIndex.row()];

    switch(aRole)
    {
        case ACTIVE_SENSOR_CALC_VALUE_ROLE:         return calcSensorData.getCalcValue(); break;

        case ACTIVE_SENSOR_CALC_DESCRIPTION_ROLE:   return calcSensorData.getDescription(); break;

        default:                                    return QVariant();
    }
}

int ActiveSensorCalcModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);
    return m_calcSensorList.count();
}

void ActiveSensorCalcModel::updateCalcValues(const SensorModel& aModel)
{
    SensorCalcModel::updateCalcValues(aModel);

    beginResetModel();
    if(0 == aModel.getSensorModelCount())
    {
        m_calcSensorList.append(CalcSensorData(tr("duration:"), 0));
    }
    else
    {

        // get start date of data
        QDateTime startDate =  aModel.getSingleSensorData(0)->getDate();

        // get end date of data
        QDateTime endDate = aModel.getSingleSensorData(aModel.getSensorModelCount() - 1)->getDate();

        // calculate duration
        const int duration = endDate.toTime_t() - startDate.toTime_t();

        // set result to model
        m_calcSensorList.append(CalcSensorData(tr("duration:"), duration));
    }
    endResetModel();
}

QHash<int, QByteArray> ActiveSensorCalcModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ACTIVE_SENSOR_CALC_VALUE_ROLE]          = "activeCalcValue";
    roles[ACTIVE_SENSOR_CALC_DESCRIPTION_ROLE]    = "activeCalcDescription";

    return roles;
}
