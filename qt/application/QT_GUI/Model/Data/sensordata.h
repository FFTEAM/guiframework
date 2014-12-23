//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensordata.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   16.12.2014 12:00:00 GMT
  *
  * @brief  Include all declarations from SensorData
  *
  */

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QString>
#include <QDateTime>

/**
 * @brief The SensorData class Store all sensor values from a single measurement
 */
class SensorData
{
    public:

        /**
         * @brief getDate GETTER-METHOD to get current time
         * @return Current time
         */
        const QDateTime& getDate () const;

        /**
         * @brief getDate GETTER-METHOD to get current heart rate
         * @return Current heart rate
         */
        quint16 getHeartRate() const;

        /**
         * @brief getStepLength GETTER-Method to get current step length
         * @return Current step length
         */
        quint16 getStepLength() const;

        /**
         * @brief setDate SETTER-Method to set new time
         * @param aDate QDateTime with new time value
         */
        void setDate(const QDateTime& aDate);

        /**
         * @brief setHeartRate SETTER-Method to set new heart rate
         * @param aHeartRate New heart rate value
         */
        void setHeartRate(quint16 aHeartRate);

        /**
         * @brief setStepLength SETTER-Method to set new step length
         * @param aStepLength New step length value
         */
        void setStepLength(quint16 aStepLength);

        /**
         * @brief getId GETTER-Method to get the id of a single measurement
         * @return Current ID of a single measurement
         */
        quint64 getId() const;

        /**
         * @brief SensorData Constructor to init all attributes
         * @param aDate         New time value
         * @param aHeartRate    New heart rate value
         * @param aStepLength   New step length value
         * @param aId           New id value
         */
        SensorData(const QDateTime &aDate, quint16 aHeartRate, quint16 aStepLength, quint64 aId);

    private:

        /**
         * @brief m_date
         * @var Time of sensor data
         */
        QDateTime m_date;

        /**
         * @brief m_heartRate
         * @var Actual heart rate
         */
        quint16 m_heartRate;

        /**
         * @brief m_stepLength
         * @var Actual step length
         */
        quint16 m_stepLength;

        /**
         * @brief m_id
         * @var Actual ID of a measurement for database
         */
        quint64 m_id;
};

#endif // SENSORDATA_H
