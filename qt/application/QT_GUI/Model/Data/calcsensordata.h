//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   calcsensordata.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef CALCSENSORDATA_H
#define CALCSENSORDATA_H

#include <QString>

class CalcSensorData
{
    public:

        CalcSensorData(const QString aDescription,const double aValue);

        QString getDescription() const;
        double getCalcValue() const ;

        void setDescription(const QString aDescription);
        void setCalcValue(const double aValue);

    private:

        QString m_Descritpion;
        double m_CalcValue;

};

#endif // CALCSENSORDATA_H
