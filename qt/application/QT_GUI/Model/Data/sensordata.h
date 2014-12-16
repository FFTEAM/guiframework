//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   sensordata.h
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 13:59:00 GMT
  *
  * @brief  Diese Header-Datei enhält alle Deklarationen der Klasse SensorData
  *
  */

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QString>

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
        QString getDate () const;

        /**
         * @brief getDate Liefert die aktuelle Herzfrequenz zurück
         * @return Aktuelle Herzfrequenz
         */
        QString getHeartRate() const;

        /**
         * @brief getStepLength Liefert die aktuelle Schrittlänge zurück
         * @return Aktuelle Schrittlänge
         */
        QString getStepLength() const;

        /**
         * @brief setDate Setzt den Wert für den Zeitstempel neu
         * @param aDate Neuer Wert für den Zeitstempel
         */
        void setDate(const QString& aDate);

        /**
         * @brief setHeartRate Setzt den Wert für die Herzfrequenz neu
         * @param aHeartRate Neuer Wert für die Herzfrequenz
         */
        void setHeartRate(const QString& aHeartRate);

        /**
         * @brief setStepLength Setzt den Wert für die Schrittlänge
         * @param aStepLength Neuer Wert für die Schrittlänge
         */
        void setStepLength(const QString& aStepLength);

        /**
         * @brief SensorData Allgemeiner Konstruktor für die Klasse SensorData
         * @param aDate Wert für den aktuellen Zeitstempel
         * @param aHeartRate Wert für die aktuelle Herzfrequenz
         * @param aStepLength Wert für die aktuelle Schrittlänge
         */
        SensorData(const QString& aDate, const QString& aHeartRate, const QString& aStepLength);

    private:

        /**
         * @brief m_date
         * @var Zeitstempel für die aktuelle Herzferquenz
         */
        QString m_date;

        /**
         * @brief m_heartRate
         * @var Enthält die aktuelle Herzfrequenz
         */
        QString m_heartRate;

        /**
         * @brief m_stepLength
         * @var Enthält die aktuelle Schrittlänge
         */
        QString m_stepLength;
};

#endif // SENSORDATA_H
