//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   ImportExport.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of ImportExport
  *
  */

#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <QObject>
#include <QDateTime>
#include <QtSql/QtSql>

#include "Model/Data/sensordata.h"
#include "Connection/DataReceiver.h"

/**
 * @class ImportExport
 * @brief The ImportExport class
 */
class ImportExport final : public QObject
{
    Q_OBJECT

    /**
     * @brief mDataBase SQLite database handler
     */
    QSqlDatabase mDataBase;

    /**
     * @brief mIsValid flag for operator bool
     */
    bool mIsValid;

    /**
     * @brief insertTypeQuery prepared query for type insertions into database
     */
    QSqlQuery insertTypeQuery;

    /**
     * @brief insertMoodQuery prepared query for mood insertions into database
     */
    QSqlQuery insertMoodQuery;

    /**
     * @brief insertMeasurementQuery prepared query for measurement insertions into database
     */
    QSqlQuery insertMeasurementQuery;

    /**
     * @brief insertDataQuery prepared query for data-point insertions into database
     */
    QSqlQuery insertDataQuery;

    /**
     * @brief ImportExport copy-constructor is disabled
     */
    ImportExport(const ImportExport&) = delete;

    /**
     * @brief operator = is disabled
     * @return not implemented
     */
    const ImportExport& operator=(const ImportExport&) = delete;

    /**
     * @brief insertTypes private method for setting up type entries in database
     *
     * Interesting if database is fresh created and has no content
     */
    void insertTypes();

    /**
     * @brief insertMoods private method for setting up mood entries in database
     *
     * Interesting if database is fresh created and has no content
     */
    void insertMoods();

public slots:
    /**
     * @brief insertMeasurement slot called by DataReceiver
     * @param dataList contains raw data-points for database insertion
     * @param type of the measurement
     * @param mood of the measurement
     * @param average heartrate of measurement
     */
    void insertMeasurement(QList<rawData>& dataList, quint8 type, quint8 mood, quint16 average);

public:
    /**
     * @brief ImportExport constructor is initializing the database connection
     * @param parent QObject of parent class
     */
    explicit ImportExport(QObject *parent = 0);

    /**
     * @brief ~ImportExport destructor is safely closing database connection
     */
    virtual ~ImportExport();

    /**
     * @brief years looks for all years for the passed measurement-type
     * @param aType the type of measurement
     * @return List of strings with year numbers in the form of YYYY
     */
    QList<QString> years(quint8 aType);

    /**
     * @brief months looks for all available months containing data
     * @param aType the type of measurement
     * @param year the year to search in
     * @return List of string with months strings (english)
     */
    QList<QString> months(quint8 aType, const QDate& year);

    /**
     * @brief dataByMeasurementId get a list of detailed data-points by id
     * @param aId the id of the measurement
     * @return List of SendorData objects, each containing a data-point of the desired measurement
     */
    QList<const SensorData*> dataByMeasurementId(quint64);

    /**
     * @brief measurements get a list of measurements by type
     * @param aType the type of measurement
     * @return List of SensorData with general information about the found measurements
     */
    QList<const SensorData*> measurements(quint8 aType);

    /**
     * @brief measurementsFromTo get a list of measurements by start and end date
     * @param aType the type of measurement
     * @param aStart start date of the measurements (inclusive)
     * @param sEnd end date of the measurements (inclusive)
     * @return List of SensorData with general information about the found measurements
     */
    QList<const SensorData*> measurementsFromTo(quint8 aType, const QDate& aStart, const QDate& sEnd);

    /**
     * @brief operator bool get information about the state of this object
     * @return true when object initialization and database setup was successful, false otherwise
     */
    explicit operator bool() const;
};

#endif // IMPORTEXPORT_H
