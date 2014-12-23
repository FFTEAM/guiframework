//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   activesensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef ACTIVESENSORCALCMODEL_H
#define ACTIVESENSORCALCMODEL_H

#include "Model/sensorcalcmodel.h"

class ActiveSensorCalcModel: public SensorCalcModel
{
    public:

        /**
         * @brief ActiveSensorCalcModel Konstruktor
         */
        ActiveSensorCalcModel(SensorModel& aModel);

        /**
         * @brief The SensorRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SensorCalcRoles
        {
            ACTIVE_SENSOR_CALC_VALUE_ROLE = 0,
            ACTIVE_SENSOR_CALC_DESCRIPTION_ROLE
        };

        /**
         * @brief data Liefert der View die zur jeweiligen Rolle gehörenden Daten
         * @param aIndex Index aktuellen Model
         * @param aRole Aktuelle Rolle
         * @return Liefert ein Wertepaar (Rolle,Wert) zurück
         */
        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        /**
         * @brief rowCount Liefert die aktuelle Anzahl der Einträge im Model zurück
         * @param aParent -
         * @return Anzahl der Einträge
         */
        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        void updateCalcValues(const SensorModel& aModel);

    protected:

        /**
         * @brief roleNames Verbindet die Rollen und die dazugehrigen Attribute der Klasse
         * @return QHash mit der Zuweisung der Rollen von der View und der Klasse
         *
         * Diese Methode wird ebenfalls vom Model/View Konzept von QT verwendet.
         */
        QHash<int, QByteArray> roleNames() const;

    private:

        /**
         * @brief m_Duration Länge einer Belastungsmessung
         */
        double m_Duration;
};

#endif // ACTIVESENSORCALCMODEL_H
