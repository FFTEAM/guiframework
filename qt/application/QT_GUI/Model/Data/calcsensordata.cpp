//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   calcsensordata.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  Implementation file of CalcSensorData class
  *
  */

#include "calcsensordata.h"

CalcSensorData::CalcSensorData(const QString aDescription, const double aValue):    m_Descritpion(aDescription),
                                                                                    m_CalcValue(aValue)
{
    // C'tor
}

QString CalcSensorData::getDescription() const
{
    return m_Descritpion;
}

double CalcSensorData::getCalcValue() const
{
    return m_CalcValue;
}

void CalcSensorData::setDescription(const QString aDescription)
{
    m_Descritpion = aDescription;
}

void CalcSensorData::setCalcValue(const double aValue)
{
    m_CalcValue = aValue;
}

