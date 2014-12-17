#include "inactivesensormodel.h"

InactiveSensorModel::InactiveSensorModel():SensorModel(0)
{
    //C'tor
    QList<const SensorData*> list;
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 123, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 180, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 10, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 200, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 80, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 100, 3));
    list.append(new SensorData(QDateTime(QDate(2015, 10, 28), QTime(20, 23, 34)), 160, 3));
    setNewSensorModel(list);
}

InactiveSensorModel& InactiveSensorModel::getInstance()
{
    static InactiveSensorModel instance;
    return instance;
}

QVariant InactiveSensorModel::data(const QModelIndex &aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();
    const SensorData* sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        case INACTIVE_SENSOR_HEART_RATE_ROLE:   return sensorData->getHeartRate(); break;

        case INACTIVE_SENSOR_DATE_ROLE:         return sensorData->getDate(); break;

        default:                                 return QVariant();
    }
}

int InactiveSensorModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);
    return m_sensorList.count();
}

QHash<int, QByteArray> InactiveSensorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[INACTIVE_SENSOR_HEART_RATE_ROLE]  = "inactiveHeartRate";
    roles[INACTIVE_SENSOR_DATE_ROLE]        = "inactiveDate";

    return roles;
}
