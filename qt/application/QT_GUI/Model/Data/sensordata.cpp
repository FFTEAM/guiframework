//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensordata.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 14:12:00 GMT
  *
  * @brief Diese CPP-Datei enthält alle Implementierung der Methoden der Klasse SensorData
  */

#include "sensordata.h"

SensorData::SensorData(const QDateTime& aDate,
                       quint16 aHeartRate,
                       quint16 aStepLength) :   m_date(aDate),
                                                       m_heartRate(aHeartRate),
                                                       m_stepLength(aStepLength)
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

quint16 SensorData::getStepLength() const
{
    return m_stepLength;
}

void SensorData::setDate(const QDateTime& aDate)
{
    m_date = aDate;
}

void SensorData::setHeartRate(quint16 aHeartRate)
{
    m_heartRate = aHeartRate;
}

void SensorData::setStepLength(quint16 aStepLength)
{
    m_stepLength = aStepLength;
}