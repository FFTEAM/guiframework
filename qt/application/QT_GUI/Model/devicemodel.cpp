#include "devicemodel.h"

DeviceModel::DeviceModel(QObject* aParent) : QAbstractListModel(aParent)
{
    // C'tor
}

void DeviceModel::addDevice(const DeviceData& aDevice)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_deviceList.append(aDevice);
    endInsertRows();
}

void DeviceModel::removeDevice(const int aIndex)
{
    if(aIndex >= 0 && aIndex < m_deviceList.size())
    {
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        m_deviceList.removeAt(aIndex);
        endRemoveRows();
    }
    else qDebug() << "Invalid Index";
}

const DeviceData* DeviceModel::getDevice(const int aIndex)
{
    if(aIndex >= 0 && aIndex < m_deviceList.size())
    {
        return &m_deviceList.at(aIndex);
    }
    else
    {
        qDebug() << "Invalid Index";
        return 0;
    }

}

void DeviceModel::updateDevice(const int aIndex, const DeviceData& aDevice)
{
    if(aIndex >= 0 && aIndex < m_deviceList.size())
    {
        beginResetModel();
        m_deviceList.replace(aIndex,aDevice);
        endResetModel();
    }
    else qDebug() << "Invalid Index";
}

void DeviceModel::clearDeviceModel()
{
    beginResetModel();
    m_deviceList.clear();
    endResetModel();
}

void DeviceModel::setNewDeviceModel(const QList<DeviceData>& aDeviceModel)
{
    beginResetModel();
    m_deviceList = aDeviceModel;
    endResetModel();
}

int DeviceModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);
    return m_deviceList.count();
}

QVariant DeviceModel::data(const QModelIndex& aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_deviceList.count()) return QVariant();

    const DeviceData& device = m_deviceList[aIndex.row()];

    switch(aRole)
    {
        case DeviceNameRole:    return device.getDeviceName(); break;
        case DeviceStatusRole:  return device.getColor(); break;
        default:                return QVariant();
    }
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DeviceNameRole]   = "deviceName";
    roles[DeviceStatusRole] = "colorState";
    return roles;
}
