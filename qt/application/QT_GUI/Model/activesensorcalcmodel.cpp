#include "activesensorcalcmodel.h"

ActiveSensorCalcModel &ActiveSensorCalcModel::getInstance()
{
    static ActiveSensorCalcModel instance;
    return instance;
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

    // get start date of data
    QDateTime startDate =  aModel.getSingleSensorData(0)->getDate();

    // get end date of data
    QDateTime endDate = aModel.getSingleSensorData(aModel.getSensorModelCount() - 1)->getDate();

    // calculate duration
    const int duration = endDate.toTime_t() - startDate.toTime_t();

    // set result to model
    m_calcSensorList.append(CalcSensorData("duration", duration));

    endResetModel();
}

QHash<int, QByteArray> ActiveSensorCalcModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ACTIVE_SENSOR_CALC_VALUE_ROLE]          = "activeCalcValue";
    roles[ACTIVE_SENSOR_CALC_DESCRIPTION_ROLE]    = "activeCalcDescription";

    return roles;
}

ActiveSensorCalcModel::ActiveSensorCalcModel()
{
    updateCalcValues(ActiveSensorModel::getInstance());
}
