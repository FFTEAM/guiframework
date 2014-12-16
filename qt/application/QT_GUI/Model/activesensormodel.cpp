#include "activesensormodel.h"

ActiveSensorModel& ActiveSensorModel::getInstance()
{
    static ActiveSensorModel instance;
    return instance;
}

QVariant ActiveSensorModel::data(const QModelIndex &aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();
    const SensorData* sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        case ACTIVE_SENSOR_HEART_RATE_ROLE:    return sensorData->getHeartRate(); break;

        case ACTIVE_SENSOR_DATE_ROLE:          return sensorData->getDate(); break;

        case ACTIVE_SENSOR_STEP_LENGTH:        return sensorData->getStepLength(); break;

        default:                                 return QVariant();
    }
}

int ActiveSensorModel::rowCount(const QModelIndex &aParent) const
{
    Q_UNUSED(aParent);
    return m_sensorList.count();
}

QHash<int, QByteArray> ActiveSensorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ACTIVE_SENSOR_HEART_RATE_ROLE]  = "activeHeartRate";
    roles[ACTIVE_SENSOR_DATE_ROLE]        = "activeDate";
    roles[ACTIVE_SENSOR_STEP_LENGTH]      = "activeStepLength";

    return roles;
}

ActiveSensorModel::ActiveSensorModel(): SensorModel(0)
{
    //C'tor
    QList<const SensorData*> list;
    list.append(new SensorData("28-10-2015 20:23:34","120","3"));
    list.append(new SensorData("28-10-2015 20:23:34","130","3"));
    list.append(new SensorData("28-10-2015 20:23:34","140","3"));
    list.append(new SensorData("28-10-2015 20:23:34","150","3"));
    list.append(new SensorData("28-10-2015 20:23:34","152","3"));
    list.append(new SensorData("28-10-2015 20:23:34","155","3"));
    list.append(new SensorData("28-10-2015 20:23:34","100","3"));
    setNewSensorModel(list);
}
