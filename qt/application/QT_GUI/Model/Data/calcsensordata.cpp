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

