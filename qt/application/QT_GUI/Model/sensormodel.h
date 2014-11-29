#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/sensordata.h"

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    public:

        enum DeviceRoles
        {
            SensorDateRole = Qt::UserRole + 1,
            SensorHeartRateRole,
            SensorStepLength
        };

        explicit SensorModel(QObject* aParent = 0);

        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        void addSensorData(const SensorData& aSensorData);

        void setNewSensorModel(const QList<SensorData>& aSensorModel);

    protected:

        QHash<int, QByteArray> roleNames() const;

    private:

        QList<SensorData> m_sensorList;

};

#endif // SENSORMODEL_H
