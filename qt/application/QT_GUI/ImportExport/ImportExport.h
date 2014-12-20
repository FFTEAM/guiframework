#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <QObject>
#include <QtSql/QtSql>

class ImportExport final : public QObject
{
    Q_OBJECT
    QSqlDatabase mDataBase;
    bool mIsValid;

    ImportExport(const ImportExport&) = delete;
    const ImportExport& operator=(const ImportExport&) = delete;

public:
    explicit ImportExport(QObject *parent = 0);
    virtual ~ImportExport();

    QStringList getMeasureValues();

    explicit operator bool() const;
};

#endif // IMPORTEXPORT_H
