#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/sensordata.h"
#include <QDebug>

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

        static SensorModel& getInstance();

        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        void addSensorData(const SensorData& aSensorData);

        void setNewSensorModel(const QList<SensorData>& aSensorModel);

        int getSensorModelCount() const;

        const SensorData* getSingleSensorData(const int aIndex) const;

    protected:

        QHash<int, QByteArray> roleNames() const;

    private:

        explicit SensorModel(QObject* aParent = 0);

        QList<SensorData> m_sensorList;

};

#endif // SENSORMODEL_H
