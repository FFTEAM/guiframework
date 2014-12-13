#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/sensordata.h"
#include <QDebug>

enum SensorDataType
{
    ACTIVE_SENSOR_DATA = 0,
    INACTIVE_SENSOR_DATA
};

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    public:

        enum SensorRoles
        {
            ACTIVE_SENSOR_DATE_ROLE = Qt::UserRole + 1,
            ACTIVE_SENSOR_HEART_RATE_ROLE,
            ACTIVE_SENSOR_STEP_LENGTH,
            INACTIVE_SENSOR_DATE_ROLE,
            INACTIVE_SENSOR_HEART_RATE_ROLE,
            INACTIVE_SENSOR_STEP_LENGTH
        };

        static SensorModel& getInstance(const SensorDataType aType);

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

        SensorModel(const SensorModel& aOther);
        SensorModel& operator= (const SensorModel& aRhs);

        QList<SensorData> m_sensorList;
};

#endif // SENSORMODEL_H
