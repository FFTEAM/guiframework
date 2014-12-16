#ifndef INACTIVESENSORMODEL_H
#define INACTIVESENSORMODEL_H

#include "Model/sensormodel.h"

class InactiveSensorModel: public SensorModel
{
    public:

        static InactiveSensorModel& getInstance();

        /**
         * @brief The SensorRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SensorRoles
        {
            INACTIVE_SENSOR_DATE_ROLE,          /**< Zeitstempel für die Herzfrequenz in einer Ruhephase */
            INACTIVE_SENSOR_HEART_RATE_ROLE     /**< Herzfrequenz in einer Ruhephase */
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

    private:

        InactiveSensorModel();
};

#endif // INACTIVESENSORMODEL_H
