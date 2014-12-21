//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   inactivesensorcalcmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef INACTIVESENSORCALCMODEL_H
#define INACTIVESENSORCALCMODEL_H

#include "Model/sensorcalcmodel.h"

class InactiveSensorCalcModel : public SensorCalcModel
{
    public:

        /**
         * @brief InactiveSensorCalcModel Constructor
         */
        InactiveSensorCalcModel(SensorModel& aModel);

        /**
         * @brief The SensorRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SensorCalcRoles
        {
            INACTIVE_SENSOR_CALC_VALUE_ROLE = 0,
            INACTIVE_SENSOR_CALC_DESCRIPTION_ROLE
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

        protected:

        /**
         * @brief roleNames Verbindet die Rollen und die dazugehrigen Attribute der Klasse
         * @return QHash mit der Zuweisung der Rollen von der View und der Klasse
         *
         * Diese Methode wird ebenfalls vom Model/View Konzept von QT verwendet.
         */
        QHash<int, QByteArray> roleNames() const;
};

#endif // INACTIVESENSORCALCMODEL_H
