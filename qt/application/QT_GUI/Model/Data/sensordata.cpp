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

SensorData::SensorData(const QString& aDate,
                       const QString& aHeartRate,
                       const QString& aStepLength) :   m_date(aDate),
                                                       m_heartRate(aHeartRate),
                                                       m_stepLength(aStepLength)
{
    // C'tor
}


QString SensorData::getDate() const
{
    return m_date;
}

QString SensorData::getHeartRate() const
{
    return m_heartRate;
}

QString SensorData::getStepLength() const
{
    return m_stepLength;
}

void SensorData::setDate(const QString& aDate)
{
    m_date = aDate;
}

void SensorData::setHeartRate(const QString& aHeartRate)
{
    m_heartRate = aHeartRate;
}

void SensorData::setStepLength(const QString& aStepLength)
{
    m_stepLength = aStepLength;
}
