#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QString>

class SensorData
{
    public:

        // READ Methods
        QString getDate () const;
        QString getHeartRate() const;
        QString getStepLength() const;

        void setDate(const QString& aDate);
        void setHeartRate(const QString& aHeartRate);
        void setStepLength(const QString& aStepLength);

        SensorData(const QString& aDate, const QString& aHeartRate, const QString& aStepLength);

    private:

        //SensorData(const SensorData& aOther);
        SensorData& operator= (const SensorData& aRhs);

        // member variables
        QString m_date;
        QString m_heartRate;
        QString m_stepLength;
};

#endif // SENSORDATA_H
