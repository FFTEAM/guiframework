#include "ImportExport.h"
#include "Settings/Settings.h"

ImportExport::ImportExport(QObject *parent) :
    QObject(parent),
    mDataBase(QSqlDatabase::addDatabase("QSQLITE"))
{
    mDataBase.setDatabaseName(Settings::getInstance().mDataDirectory + "/pastMeasurements.db3");
    qDebug() << mDataBase.databaseName();
    mDataBase.open();
}



ImportExport::~ImportExport()
{
    mDataBase.close();
}
