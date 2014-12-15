#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver : public QObject
{
    Q_OBJECT
public:
    DataReceiver();

public slots:
    bool validateData(const QString&);
};

#endif // DATARECEIVER_H

