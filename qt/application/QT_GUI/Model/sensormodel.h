//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensormodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 14:07:00 GMT
  *
  * @brief  Diese Header-Datei enhält alle Deklarationen der Klasse SensoModel
  *
  */

#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/Data/sensordata.h"
#include <QDebug>

/**
 * @brief The SensorDataType enum
 */
enum SensorDataType
{
    ACTIVE_SENSOR_DATA = 0, /**< Sensor Daten während der Belastung */
    INACTIVE_SENSOR_DATA    /**< Sensor Daten während der Ruhephase */
};

/**
 * @brief The SensorModel class
 *
 * Diese Klasse fungiert als Model für das Model/ View Konzept. In diesem Zusammenhang besitzt
 * diese Klasse eine Liste mit Elementen der Klasse SensorData. Diese Liste repräsentiert die Daten, welche
 * durch das Model verwaltet wird. Wird eine Änderung an dem Datenbestand durchgeführt, aktualisiert sich
 * automatische die View mit dem neuen Datenbestand. Diese Aufgabe wird mit Hilfe dieser Klasse realisert.
 * Des weiteren ist diese Klasse als Singleton Pattern modeliert worden. Dies besitzt den Vorteil, dass
 * das Model Global an allen Stellen in der Applikation verwendet werden kann und nicht mehrmals neu
 * erzuegt werden muss.
 */
class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    public:

        /**
         * @brief The SensorRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SensorRoles
        {
            ACTIVE_SENSOR_DATE_ROLE = Qt::UserRole + 1,     /**< Zeitstempel für die Herzfrequenz unter Belastung */
            ACTIVE_SENSOR_HEART_RATE_ROLE,                  /**< Herzfrequenz unter Belastung */
            ACTIVE_SENSOR_STEP_LENGTH,                      /**< Schrittlänge unter Belastung */
            INACTIVE_SENSOR_DATE_ROLE,                      /**< Zeitstempel für die Herzfrequenz in einer Ruhephase */
            INACTIVE_SENSOR_HEART_RATE_ROLE,                /**< Herzfrequenz in einer Ruhephase */
            INACTIVE_SENSOR_STEP_LENGTH
        };

        /**
         * @brief getInstance Liefert ein Objekt der Klasse SensorModel zurück
         * @param aType Gibt den Type von Messdaten an
         * @return  Objekt der vom type abhängigen Messdaten
         */
        static SensorModel& getInstance(const SensorDataType aType);
        ~SensorModel();

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

        /**
         * @brief addSensorData Fügt ein neues Datenobjekt dem Model hinzu
         * @param aSensorData Neues Datenenobjekt
         */
        void addSensorData(const SensorData* aSensorData);

        /**
         * @brief setNewSensorModel Fügt eine neue Menge an Datenobjekten dem Model hinzu
         * @param aSensorModel Liste mit neuen Datenobjekten
         */
        void setNewSensorModel(const QList<const SensorData*> &aSensorModel);

        /**
         * @brief getSensorModelCount Liefert die Anzahl an Datenobjekten im Model zurück
         * @return Anzahl der Datenobjekte
         */
        int getSensorModelCount() const;

        /**
         * @brief getSingleSensorData Liefert ein einzelnes Datenobjekt zurück
         * @param aIndex Index des Datenobjektes
         * @return Ausgewähltes Datenobjekt
         */
        const SensorData* getSingleSensorData(const int aIndex) const;

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
         * @brief SensorModel ist der Standardtkonstruktor der Klasse SensorModel
         * @param aParent Zeiger auf die Basisklasse QObject
         */
        explicit SensorModel(QObject* aParent = 0);

        /**
         * @brief  SensorModel Nicht in Verwendung (Definition fehlt)
         * @param aOther Referenz auf ein Objekt der Klasse SensorModel
         */
        SensorModel(const SensorModel& aOther);

        /**
         * @brief  cleanList Gibt Speicher aller SensoDaten frei und clear die m_sensorList
         */
        void cleanList();

        /**
         * @brief operator = Nicht in Verwendung (Definition fehlt)
         * @param aRhs Referenz auf ein Objekt der Klasse SensorModel
         * @return Liefert ein Objekt der Klasse SensorModel zurück (Konkatination möglich)
         */
        SensorModel& operator= (const SensorModel& aRhs);

        /**
         * @brief m_sensorList Liste mit den aktuellen Datenobjekten
         */
        QList<const SensorData*> m_sensorList;
};

#endif // SENSORMODEL_H
