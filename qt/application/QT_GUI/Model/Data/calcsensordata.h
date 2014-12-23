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
  * @brief  Include all declarations from CalcSensorData
  *
  */

#ifndef CALCSENSORDATA_H
#define CALCSENSORDATA_H

#include <QString>

/**
 * @brief The CalcSensorData class Store all calculate values in a single class
 */
class CalcSensorData
{
    public:

        /**
         * @brief CalcSensorData Constructor to init all attributes
         * @param aDescription  Description of calculate data
         * @param aValue        Value from the calculate data
         */
        CalcSensorData(const QString aDescription,const double aValue);

        /**
         * @brief getDescription GETTER-Method to get the current description
         * @return  Current description
         */
        QString getDescription() const;

        /**
         * @brief getCalcValue GETTER-Method to get the current calculate value
         * @return Current value
         */
        double getCalcValue() const ;

        /**
         * @brief setDescription SETTER-Method to set the current description
         * @param aDescription  QString with the new description
         */
        void setDescription(const QString aDescription);

        /**
         * @brief setCalcValue SETTER-Method to set the current value
         * @param aValue    Double Type with the new value
         */
        void setCalcValue(const double aValue);

    private:

        /**
         * @brief m_Descritpion
         * @var QString with the description
         */
        QString m_Descritpion;

        /**
         * @brief m_CalcValue
         * @var Double with the calculate value
         */
        double m_CalcValue;
};

#endif // CALCSENSORDATA_H
