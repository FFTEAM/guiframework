#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

#include "devicedata.h"

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT

    public:

        enum DeviceRoles
        {
                DeviceNameRole = Qt::UserRole + 1,
                DeviceStatusRole
        };

        explicit DeviceModel(QObject* aParent = 0);

        void addDevice(const DeviceData& aDevice);

        void removeDevice(const int aIndex);

        void updateDevice(const int aIndex, const DeviceData& aDevice);

        void clearDeviceModel();

        void setNewDeviceModel(const QList<DeviceData>& aDeviceModel);

        const DeviceData& getDevice(const int aIndex);

        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

    protected:

        QHash<int, QByteArray> roleNames() const;

    private:

        QList<DeviceData> m_deviceList;
};

#endif // DEVICEMODEL_H
