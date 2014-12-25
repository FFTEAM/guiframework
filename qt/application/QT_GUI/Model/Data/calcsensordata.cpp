//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   calcsensordata.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   14.12.2014 13:01:00 GMT
  *
  * @brief  Implementation file of CalcSensorData class
  *
  */

#include "calcsensordata.h"

CalcSensorData::CalcSensorData(const QString aDescription,
                               const double aValue,
                               const QString aUnit):   m_Descritpion(aDescription),
                                                       m_CalcValue(aValue),
                                                       m_UnitOfMeasurement(aUnit)
{
    // C'tor
}

QString CalcSensorData::getUnitOfMeasurement() const
{
    return m_UnitOfMeasurement;
}

QString CalcSensorData::getDescription() const
{
    return m_Descritpion;
}

double CalcSensorData::getCalcValue() const
{
    return m_CalcValue;
}

void CalcSensorData::setUnitOfMeasurement(const QString aUnit)
{
    m_UnitOfMeasurement = aUnit;
}

void CalcSensorData::setDescription(const QString aDescription)
{
    m_Descritpion = aDescription;
}

void CalcSensorData::setCalcValue(const double aValue)
{
    m_CalcValue = aValue;
}

