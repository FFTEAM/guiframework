#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <QObject>
#include <QtSql/QtSql>

class ImportExport : public QObject
{
    Q_OBJECT
    QSqlDatabase mDataBase;

    ImportExport(const ImportExport&);
    const ImportExport& operator=(const ImportExport&);

public:
    explicit ImportExport(QObject *parent = 0);
    virtual ~ImportExport();
};

#endif // IMPORTEXPORT_H
