#include "ImportExport.h"

ImportExport::ImportExport(QObject *parent) :
    QObject(parent),
    mDataBase(QSqlDatabase::addDatabase("QSQLITE"))
{
    mDataBase.setDatabaseName("fileName.db3");
    mDataBase.open();
}

ImportExport::~ImportExport()
{
    mDataBase.close();
}
