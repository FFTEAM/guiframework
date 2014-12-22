//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensordata.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QString>
#include <QDateTime>

/**
 * @brief The SensorData class
 *
 * Diese Klasse kapselt einen Datensatz an Sensordaten, welche durch die Smartwatch generiert wird.
 * Das spätere Model enthält eine Liste von Datenobjekten dieser Klasse.
 */
class SensorData
{
    public:

        /**
         * @brief getDate Liefert den Zeitstempel zur Herzfrequenz zurück
         * @return Zeitstempel zur Herzfrequenz
         */
        const QDateTime& getDate () const;

        /**
         * @brief getDate Liefert die aktuelle Herzfrequenz zurück
         * @return Aktuelle Herzfrequenz
         */
        quint16 getHeartRate() const;

        /**
         * @brief getStepLength Liefert die aktuelle Schrittlänge zurück
         * @return Aktuelle Schrittlänge
         */
        quint16 getStepLength() const;

        /**
         * @brief setDate Setzt den Wert für den Zeitstempel neu
         * @param aDate Neuer Wert für den Zeitstempel
         */
        void setDate(const QDateTime& aDate);

        /**
         * @brief setHeartRate Setzt den Wert für die Herzfrequenz neu
         * @param aHeartRate Neuer Wert für die Herzfrequenz
         */
        void setHeartRate(quint16 aHeartRate);

        /**
         * @brief setStepLength Setzt den Wert für die Schrittlänge
         * @param aStepLength Neuer Wert für die Schrittlänge
         */
        void setStepLength(quint16 aStepLength);

        /**
         * @brief SensorData Allgemeiner Konstruktor für die Klasse SensorData
         * @param aDate Wert für den aktuellen Zeitstempel
         * @param aHeartRate Wert für die aktuelle Herzfrequenz
         * @param aStepLength Wert für die aktuelle Schrittlänge
         */
        SensorData(const QDateTime &aDate, quint16 aHeartRate, quint16 aStepLength, quint64 aId);

    private:

        /**
         * @brief m_date
         * @var Zeitstempel für die aktuelle Herzferquenz
         */
        QDateTime m_date;

        /**
         * @brief m_heartRate
         * @var Enthält die aktuelle Herzfrequenz
         */
        quint16 m_heartRate;

        /**
         * @brief m_stepLength
         * @var Enthält die aktuelle Schrittlänge
         */
        quint16 m_stepLength;

        /**
         * @brief m_id id for db
         */
        quint64 m_id;
};

#endif // SENSORDATA_H
