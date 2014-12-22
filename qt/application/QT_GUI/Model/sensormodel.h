//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensormodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include "Model/Data/sensordata.h"
#include <QDebug>

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

        friend class SensorCalcModel;

        /**
         * @brief The SensorRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SensorRoles
        {
            SENSOR_DATE_ROLE,            /**< Zeitstempel für die Herzfrequenz  */
            SENSOR_HEART_RATE_ROLE,      /**< Herzfrequenz */
            SENSOR_STEP_LENGTH_ROLE      /**< Schrittlänge */
        };

        ~SensorModel();

        SensorModel();

        SensorModel(const SensorModel& aOther);

        QList<const SensorData*> getDataList() const;

        /**
         * @brief addSensorData Fügt ein neues Datenobjekt dem Model hinzu
         * @param aSensorData Neues Datenenobjekt
         */
        void addSensorData(const SensorData* aSensorData);

        /**
         * @brief setNewSensorModel Fügt eine neue Menge an Datenobjekten dem Model hinzu
         * @param aSensorModel Liste mit neuen Datenobjekten
         */
        void setNewSensorModel(QList<const SensorData*>& aSensorModel);

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

        /**
         * @brief  cleanList Gibt Speicher aller SensoDaten frei und clear die m_sensorList
         */
        void cleanList();

        /**
         * @brief m_sensorList Liste mit den aktuellen Datenobjekten
         */
        QList<const SensorData*> m_sensorList;

};

#endif // SENSORMODEL_H
