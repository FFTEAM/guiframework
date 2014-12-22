#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <QObject>
#include <QtSql/QtSql>

#include "Model/Data/sensordata.h"
#include "Connection/DataReceiver.h"

class ImportExport final : public QObject
{
    Q_OBJECT
    QSqlDatabase mDataBase;
    bool mIsValid;

    QSqlQuery insertTypeQuery;
    QSqlQuery insertMoodQuery;
    QSqlQuery insertMeasurementQuery;
    QSqlQuery insertDataQuery;

    ImportExport(const ImportExport&) = delete;
    const ImportExport& operator=(const ImportExport&) = delete;

    void insertTypes();
    void insertMoods();

public slots:
    void insertMeasurement(QList<rawData>&, quint8 type, quint8 mood, quint16 average);

public:
    explicit ImportExport(QObject *parent = 0);
    virtual ~ImportExport();

    QStringList getMeasureValues();

    explicit operator bool() const;
};

#endif // IMPORTEXPORT_H
