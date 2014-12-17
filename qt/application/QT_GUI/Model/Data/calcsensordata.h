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
