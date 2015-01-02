//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensordata.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   16.12.2014 12:02:00 GMT
  *
  * @brief  Implementation file of SensorData class
  *
  */

#include "sensordata.h"

SensorData::SensorData(const QDateTime& aDate,
                       quint16 aHeartRate,
                       quint16 aStepCount,
                       quint64 aId) :   m_date(aDate),
                                        m_heartRate(aHeartRate),
                                        m_stepCount(aStepCount),
                                        m_id(aId)
{
    // C'tor
}


const QDateTime &SensorData::getDate() const
{
    return m_date;
}

quint16 SensorData::getHeartRate() const
{
    return m_heartRate;
}

quint16 SensorData::getStepCount() const
{
    return m_stepCount;
}

void SensorData::setDate(const QDateTime& aDate)
{
    m_date = aDate;
}

void SensorData::setHeartRate(quint16 aHeartRate)
{
    m_heartRate = aHeartRate;
}

void SensorData::setStepCount(quint16 aStepCount)
{
    m_stepCount = aStepCount;
}

quint64 SensorData::getId() const
{
    return m_id;
}
