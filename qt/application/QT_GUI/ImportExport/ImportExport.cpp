#include "ImportExport.h"
#include "Settings/Settings.h"

ImportExport::ImportExport(QObject *parent) :
    QObject(parent),
    mDataBase(QSqlDatabase::addDatabase("QSQLITE")),
    mIsValid(false)
{
    mDataBase.setDatabaseName(Settings::getInstance().mDataDirectory + "/pastMeasurements.db3");
    qDebug() << mDataBase.databaseName();

    if (!mDataBase.open())
    {
        qDebug() << mDataBase.lastError().databaseText();
    }

    QString createTableType =
            "CREATE TABLE IF NOT EXISTS Type("
            "id UNSIGNED INTEGER PRIMARY KEY, "
            "name VARCHAR(100)"
            ");";

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

    QSqlQuery createTable(mDataBase);
    if (!createTable.exec(createTableType))
    {
        qDebug() << createTable.lastError().databaseText();
    }
    else if (!createTable.exec(createTableMood))
    {
        qDebug() << createTable.lastError().databaseText();
    }
    else if (!createTable.exec(createTableMeasurement))
    {
        qDebug() << createTable.lastError().databaseText();
    }
    else if (!createTable.exec(createTableData))
    {
        qDebug() << createTable.lastError().databaseText();
    }

    mIsValid = true;
}

ImportExport::~ImportExport()
{
    mDataBase.close();
}


ImportExport::operator bool() const
{
    return mIsValid;
}
