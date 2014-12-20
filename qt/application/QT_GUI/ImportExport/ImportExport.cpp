#include "ImportExport.h"
#include "Settings/Settings.h"

ImportExport::ImportExport(QObject *parent) :
    QObject(parent),
    mDataBase(QSqlDatabase::addDatabase("QSQLITE")),
    mIsValid(false),
    insertTypeQuery(mDataBase),
    insertMoodQuery(mDataBase),
    insertMeasurementQuery(mDataBase),
    insertDataQuery(mDataBase)
{
    mDataBase.setDatabaseName(Settings::getInstance().mDataDirectory + "/pastMeasurements.db3");
    qDebug() << mDataBase.databaseName();

    /*QString createTableType =
            "CREATE TABLE IF NOT EXISTS Type("
            "id UNSIGNED INTEGER PRIMARY KEY, "
            "name VARCHAR(100)"
            ");";*/

    QString createTableMood =
            "CREATE TABLE IF NOT EXISTS Mood("
            "id UNSIGNED INTEGER PRIMARY KEY, "
            "name VARCHAR(100)"
            ");";

    QString createTableMeasurement =
            "CREATE TABLE IF NOT EXISTS Measurement("
            "id UNSIGNED INTEGER PRIMARY KEY, "
            "type UNSIGNED INTEGER, "
            "mood UNSIGNED INTEGER, "
            "average UNSIGNED INTEGER, "
            "timestamp UNSIGNED INTEGER, "
            "duration UNSIGNED INTEGER, "
            "FOREIGN KEY(type) REFERENCES Type(id), "
            "FOREIGN KEY(mood) REFERENCES Mood(id)"
            ");";

    QString createTableData =
            "CREATE TABLE IF NOT EXISTS Data("
            "id UNSIGNED INTEGER PRIMARY KEY, "
            "measurement UNSIGNED INTEGER, "
            "seconds UNSIGNED INTEGER, "
            "heartrate UNSIGNED INTEGER, "
            "steps UNSIGNED INTEGER, "
            "FOREIGN KEY(measurement) REFERENCES Measurement(id)"
            ");";

    if (!mDataBase.open())
    {
        qDebug() << mDataBase.lastError().databaseText();
    }
    else
    {
        QSqlQuery createTable(mDataBase);
        if (!createTable.exec(
                    "CREATE TABLE IF NOT EXISTS Type("
                    "id UNSIGNED INTEGER PRIMARY KEY, "
                    "name VARCHAR(100)"
                    ");")
           )
        {
            qDebug() << createTable.lastError().databaseText();
        }
        else if (!createTable.exec(
                     "CREATE TABLE IF NOT EXISTS Mood("
                     "id UNSIGNED INTEGER PRIMARY KEY, "
                     "name VARCHAR(100)"
                     ");")
                )
        {
            qDebug() << createTable.lastError().databaseText();
        }
        else if (!createTable.exec(
                     "CREATE TABLE IF NOT EXISTS Measurement("
                     "id UNSIGNED INTEGER PRIMARY KEY, "
                     "type UNSIGNED INTEGER, "
                     "mood UNSIGNED INTEGER, "
                     "average UNSIGNED INTEGER, "
                     "timestamp UNSIGNED INTEGER, "
                     "duration UNSIGNED INTEGER, "
                     "FOREIGN KEY(type) REFERENCES Type(id), "
                     "FOREIGN KEY(mood) REFERENCES Mood(id)"
                     ");")
                )
        {
            qDebug() << createTable.lastError().databaseText();
        }
        else if (!createTable.exec(
                     "CREATE TABLE IF NOT EXISTS Data("
                     "id UNSIGNED INTEGER PRIMARY KEY, "
                     "measurement UNSIGNED INTEGER, "
                     "seconds UNSIGNED INTEGER, "
                     "heartrate UNSIGNED INTEGER, "
                     "steps UNSIGNED INTEGER, "
                     "FOREIGN KEY(measurement) REFERENCES Measurement(id)"
                     ");")
                )
        {
            qDebug() << createTable.lastError().databaseText();
        }
        else
        {
            // everthing above was okay!
            // now the statements we use are prepared:
            if (!insertTypeQuery.prepare("INSERT INTO Type(name) VALUES(:name);"))
            {
                qDebug() << insertTypeQuery.lastError().databaseText();
            }
            else if (!insertMoodQuery.prepare("INSERT INTO Mood(name) VALUES(:name);"))
            {
                qDebug() << insertMoodQuery.lastError().databaseText();
            }
            else if (!insertMeasurementQuery.prepare("INSERT INTO Measurement(type, mood, average, timestamp, duration) VALUES(:type, :mood, :average, :timestamp, :duration);"))
            {
                qDebug() << insertMeasurementQuery.lastError().databaseText();
            }
            else if (!insertDataQuery.prepare("INSERT INTO Data(measurement, seconds, heartrate, steps) VALUES(:measurement, :seconds, :heartrate, :steps);"))
            {
                qDebug() << insertMoodQuery.lastError().databaseText();
            }

            mIsValid = true;
        }
    }
}

/*
 * Eingabe Jahr: Ausgabe Monate in denen Messung vorhanden
 * Eingabe Monat: Ausgabe wochen
 * Eingabe Wochen: Ausgabe aller Messungen
*/

ImportExport::~ImportExport()
{
    mDataBase.close();
}

ImportExport::operator bool() const
{
    return mIsValid;
}
