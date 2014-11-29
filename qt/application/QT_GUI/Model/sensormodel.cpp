#include "sensormodel.h"

SensorModel::SensorModel(QObject* aParent) : QAbstractListModel(aParent)
{
    // C'tor
}

QVariant SensorModel::data(const QModelIndex& aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();

    const SensorData& sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        case SensorHeartRateRole:   return sensorData.getHeartRate(); break;
        case SensorDateRole:        return sensorData.getDate(); break;
        case SensorStepLength:      return sensorData.getStepLength(); break;
        default:                    return QVariant();
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

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[SensorHeartRateRole]  = "heartRate";
    roles[SensorDateRole]       = "date";
    roles[SensorStepLength]     = "stepLength";
    return roles;
}
