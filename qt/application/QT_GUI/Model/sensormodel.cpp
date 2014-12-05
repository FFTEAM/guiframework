#include "sensormodel.h"

SensorModel::SensorModel(QObject* aParent) : QAbstractListModel(aParent)
{
    // C'tor
}

SensorModel &SensorModel::getInstance()
{
    static SensorModel instance;
    return instance;
}

QVariant SensorModel::data(const QModelIndex& aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_sensorList.count()) return QVariant();

    const SensorData& sensorData = m_sensorList[aIndex.row()];

    switch(aRole)
    {
        // To Do
        // Its is possible to divide inactive puls rate and aktive puls rate
        // Add more roles
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

    roles[SensorHeartRateRole]  = "heartRate";
    roles[SensorDateRole]       = "date";
    roles[SensorStepLength]     = "stepLength";
    return roles;
}
