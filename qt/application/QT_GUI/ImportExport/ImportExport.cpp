#include "ImportExport.h"
#include "MeasureType.h"
#include "MoodType.h"
#include "Settings/Settings.h"

ImportExport::ImportExport(QObject *parent) :
    QObject(parent),
    mDataBase(QSqlDatabase::addDatabase("QSQLITE")),
    mIsValid(false),
    insertTypeQuery(),
    insertMoodQuery(),
    insertMeasurementQuery(),
    insertDataQuery()
{
    mDataBase.setDatabaseName(Settings::getInstance().mDataDirectory + "/pastMeasurements.db3");

    if (!mDataBase.open())
    {
        qDebug() << "FATAL open(): " << mDataBase.lastError().databaseText();
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
            qDebug() << "FATAL exec(): " << createTable.lastError().databaseText();
        }
        else if (!createTable.exec(
                     "CREATE TABLE IF NOT EXISTS Mood("
                     "id UNSIGNED INTEGER PRIMARY KEY, "
                     "name VARCHAR(100)"
                     ");")
                )
        {
            qDebug() << "FATAL exec(): " << createTable.lastError().databaseText();
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
            qDebug() << "FATAL exec(): " << createTable.lastError().databaseText();
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
            qDebug() << "FATAL exec(): " << createTable.lastError().databaseText();
        }
        else
        {
            // everthing above was okay!
            // now the statements we use are prepared

            // first set the sqlqueries to the database:
            insertTypeQuery =  QSqlQuery(mDataBase);
            insertMoodQuery =  QSqlQuery(mDataBase);
            insertMeasurementQuery =  QSqlQuery(mDataBase);
            insertDataQuery =  QSqlQuery(mDataBase);
            if (!insertTypeQuery.prepare("INSERT OR REPLACE INTO Type(id, name) VALUES(:id, :name);"))
            {
                qDebug() << "FATAL insertTypeQuery.prepare(): " << insertTypeQuery.lastError().databaseText() << " - " << insertTypeQuery.lastError().driverText();
            }
            else if (!insertMoodQuery.prepare("INSERT OR REPLACE INTO Mood(id, name) VALUES(:id, :name);"))
            {
                qDebug() << "FATAL insertMoodQuery.prepare(): " << insertMoodQuery.lastError().databaseText() << " - " << insertMoodQuery.lastError().driverText();
            }
            else if (!insertMeasurementQuery.prepare("INSERT INTO Measurement(type, mood, average, timestamp, duration) VALUES(:type, :mood, :average, :timestamp, :duration);"))
            {
                qDebug() << "FATAL insertMeasurementQuery.prepare(): " << insertMeasurementQuery.lastError().databaseText() << " - " << insertMeasurementQuery.lastError().driverText();
            }
            else if (!insertDataQuery.prepare("INSERT INTO Data(measurement, seconds, heartrate, steps) VALUES(:measurement, :seconds, :heartrate, :steps);"))
            {
                qDebug() << "FATAL insertDataQuery.prepare(): " << insertDataQuery.lastError().databaseText() << " - " << insertDataQuery.lastError().driverText();
            }
            else
            {
                insertTypes();
                insertMoods();
                connect(&DataReceiver::getInstance(), SIGNAL(updateStorage(QList<rawData>&,quint8,quint8,quint16)), this, SLOT(insertMeasurement(QList<rawData>&,quint8,quint8,quint16)));
                mIsValid = true;
            }
        }
    }
}

/*
 * Eingabe Jahr: Ausgabe Monate in denen Messung vorhanden
 * Eingabe Monat: Ausgabe wochen
 * Eingabe Wochen: Ausgabe aller Messungen
*/

void ImportExport::insertTypes()
{
    mDataBase.transaction();

    for (quint8 i = 0; i < MeasureType::numOfTypes; i++)
    {
        insertTypeQuery.bindValue(":id", i);
        insertTypeQuery.bindValue(":name", MeasureType::typeName[i]);
        if (!insertTypeQuery.exec())
        {
            qDebug() << "FATAL insertTypeQuery.exec(): " << insertTypeQuery.lastError().databaseText() << " - " << insertTypeQuery.lastError().driverText();
            qDebug() << "Executed Query: " << insertTypeQuery.executedQuery();
            mDataBase.rollback();

            return;
        }
        insertTypeQuery.finish();
    }

    mDataBase.commit();
}

void ImportExport::insertMoods()
{
    mDataBase.transaction();

    for (quint8 i = 0; i < MoodType::numOfTypes; i++)
    {
        insertMoodQuery.bindValue(":id", i);
        insertMoodQuery.bindValue(":name", MoodType::typeName[i]);
        if (!insertMoodQuery.exec())
        {
            qDebug() << "FATAL insertMoodQuery.exec(): " << insertMoodQuery.lastError().databaseText() << " - " << insertMoodQuery.lastError().driverText();
            qDebug() << "Executed Query: " << insertMoodQuery.executedQuery();
            mDataBase.rollback();

            return;
        }
        insertMoodQuery.finish();
    }   

    mDataBase.commit();
}

void ImportExport::insertMeasurement(QList<rawData>& dataList, quint8 type, quint8 mood, quint16 average)
{
    if (!dataList.size())
    {
        return;
    }

    quint64 dataEntries = dataList.size();
    quint64 timestamp = dataList[0].timeStamp; // starttime
    quint64 duration = dataList[dataEntries-1].timeStamp - timestamp; // endtime

    mDataBase.transaction();

    insertMeasurementQuery.bindValue(":type", type);
    insertMeasurementQuery.bindValue(":mood", mood);
    insertMeasurementQuery.bindValue(":average", average);
    insertMeasurementQuery.bindValue(":timestamp", timestamp);
    insertMeasurementQuery.bindValue(":duration", duration);

    if (!insertMeasurementQuery.exec())
    {
        qDebug() << "FATAL insertMeasurementQuery.exec(): " << insertMeasurementQuery.lastError().databaseText() << " - " << insertMeasurementQuery.lastError().driverText();
        qDebug() << "Executed Query: " << insertMeasurementQuery.executedQuery();
        mDataBase.rollback();

        return;
    }
    QVariant res = insertMeasurementQuery.lastInsertId();
    if (!res.isValid())
    {
        qDebug() << "INVALID lastInsertId()!";
        mDataBase.rollback();

        return;
    }
    quint64 measurementId = res.toInt(0);

    for (quint64 i = 0; i < dataEntries; i++)
    {
        insertDataQuery.bindValue(":measurement", measurementId);
        insertDataQuery.bindValue(":seconds", dataList[i].timeStamp - timestamp);
        insertDataQuery.bindValue(":heartrate", dataList[i].heartRate);
        insertDataQuery.bindValue(":steps", dataList[i].steps);

        if (!insertDataQuery.exec())
        {
            qDebug() << "FATAL insertDataQuery.exec(): " << insertDataQuery.lastError().databaseText() << " - " << insertDataQuery.lastError().driverText();
            qDebug() << "Executed Query: " << insertDataQuery.executedQuery();

            mDataBase.rollback();

            return;
        }
        insertDataQuery.finish();
    }

    mDataBase.commit();
}

/** getter
 */

QList<const SensorData*> ImportExport::measurements(quint8 aType)
{
    QList<const SensorData*> dataList;
    QSqlQuery selectMeasurement(mDataBase);
    selectMeasurement.prepare(
                "SELECT "
                    "m.id, "
                    "m.average, "
                    "m.timestamp, "
                    "m.duration, "
                    "Type.name, "
                    "Mood.name "
                "FROM "
                    "Measurement m "
                "INNER JOIN "
                    "Type, "
                    "Mood "
                "ON "
                    "m.type=Type.id "
                "AND "
                    "m.mood=Mood.id "
                "WHERE "
                    "m.type = :type;"
                );
    selectMeasurement.bindValue(":type", aType);

    if (!selectMeasurement.exec())
    {
        qDebug() << "FATAL selectMeasurement.exec(): " << selectMeasurement.lastError().databaseText() << " - " << selectMeasurement.lastError().driverText();
        qDebug() << "Executed Query: " << selectMeasurement.executedQuery();

        return dataList;
    }

    quint64 measurementId;
    quint64 average;
    quint64 timestamp;
    quint64 duration;
    QString type;
    QString mood;

    while (selectMeasurement.next())
    {
        measurementId = selectMeasurement.value(0).toInt();
        average = selectMeasurement.value(1).toInt();
        timestamp = selectMeasurement.value(2).toLongLong();
        duration = selectMeasurement.value(3).toInt();
        type = selectMeasurement.value(4).toString();
        mood = selectMeasurement.value(5).toString();

        dataList.push_back(new SensorData(QDateTime().fromMSecsSinceEpoch(timestamp), average, duration, measurementId));
    }

    selectMeasurement.finish();

    return dataList;
}

QList<const SensorData*> ImportExport::measurementsFromTo(quint8 aType, const QDate& aStart, const QDate& sEnd)
{
    quint64 startTimeStamp = QDateTime(aStart).toMSecsSinceEpoch();
    quint64 endTimeStamp = QDateTime(sEnd).addDays(1).toMSecsSinceEpoch();

    QList<const SensorData*> dataList;
    QSqlQuery selectMeasurement(mDataBase);
    selectMeasurement.prepare(
                "SELECT "
                    "m.id, "
                    "m.average, "
                    "m.timestamp, "
                    "m.duration, "
                    "Type.name, "
                    "Mood.name "
                "FROM "
                    "Measurement m "
                "INNER JOIN "
                    "Type, "
                    "Mood "
                "ON "
                    "m.type=Type.id "
                "AND "
                    "m.mood=Mood.id "
                "WHERE "
                    "m.timestamp >= :startTimeStamp "
                "AND "
                    "m.timestamp <= :endTimeStamp "
                "AND "
                    "m.type = :type;"
                );
    selectMeasurement.bindValue(":startTimeStamp", startTimeStamp);
    selectMeasurement.bindValue(":endTimeStamp", endTimeStamp);
    selectMeasurement.bindValue(":type", aType);

    if (!selectMeasurement.exec())
    {
        qDebug() << "FATAL selectMeasurement.exec(): " << selectMeasurement.lastError().databaseText() << " - " << selectMeasurement.lastError().driverText();
        qDebug() << "Executed Query: " << selectMeasurement.executedQuery();

        return dataList;
    }

    quint64 measurementId;
    quint64 average;
    quint64 timestamp;
    quint64 duration;
    QString type;
    QString mood;

    while (selectMeasurement.next())
    {
        measurementId = selectMeasurement.value(0).toInt();
        average = selectMeasurement.value(1).toInt();
        timestamp = selectMeasurement.value(2).toLongLong();
        duration = selectMeasurement.value(3).toInt();
        type = selectMeasurement.value(4).toString();
        mood = selectMeasurement.value(5).toString();

        dataList.push_back(new SensorData(QDateTime().fromMSecsSinceEpoch(timestamp), average, duration, measurementId));
    }

    selectMeasurement.finish();

    return dataList;
}

QList<QString> ImportExport::years(quint8 aType)
{
    QList<QString> dataList;

    QSqlQuery selectMeasurement(mDataBase);
    selectMeasurement.prepare(
                "SELECT "
                    "timestamp "
                "FROM "
                    "Measurement "
                "WHERE "
                    "type = :type;"
                );

    selectMeasurement.bindValue(":type", aType);

    if (!selectMeasurement.exec())
    {
        qDebug() << "FATAL selectMeasurement.exec(): " << selectMeasurement.lastError().databaseText() << " - " << selectMeasurement.lastError().driverText();
        qDebug() << "Executed Query: " << selectMeasurement.executedQuery();

        return dataList;
    }

    quint64 timestamp;

    QString yearStr;

    while (selectMeasurement.next())
    {
        timestamp = selectMeasurement.value(0).toLongLong();

        QDateTime yearDate = QDateTime::fromMSecsSinceEpoch(timestamp);
        yearStr = yearDate.toString("yyyy");

        if (!dataList.contains(yearStr))
        {
            dataList.push_back(yearStr);
        }
    }

    selectMeasurement.finish();

    return dataList;
}

QList<const SensorData*> ImportExport::dataByMeasurementId(quint64 aId)
{
    QList<const SensorData*> dataList;
    QSqlQuery selectMeasurement(mDataBase);
    selectMeasurement.prepare(
                "SELECT "
                    "seconds, heartrate, steps "
                "FROM "
                    "Data "
                "WHERE "
                    "measurement >= :id;"
                );

    selectMeasurement.bindValue(":id", aId);

    if (!selectMeasurement.exec())
    {
        qDebug() << "FATAL selectMeasurement.exec(): " << selectMeasurement.lastError().databaseText() << " - " << selectMeasurement.lastError().driverText();
        qDebug() << "Executed Query: " << selectMeasurement.executedQuery();

        return dataList;
    }

    quint64 seconds;
    quint64 heartrate;
    quint64 steps;

    while (selectMeasurement.next())
    {
        seconds = selectMeasurement.value(0).toLongLong();
        heartrate = selectMeasurement.value(1).toInt();
        steps = selectMeasurement.value(2).toLongLong();

        dataList.push_back(new SensorData(QDateTime().fromMSecsSinceEpoch(seconds), heartrate, steps, aId));
    }

    selectMeasurement.finish();

    return dataList;
}

ImportExport::~ImportExport()
{
    mDataBase.close();
}

ImportExport::operator bool() const
{
    return mIsValid;
}
