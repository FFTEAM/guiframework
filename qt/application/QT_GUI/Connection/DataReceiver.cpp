#include "DataReceiver.h"

#include <QDebug>

DataReceiver::DataReceiver()
{
}

bool DataReceiver::validateData(const QString& msg)
{
    qDebug() << msg;
    return true;
}
