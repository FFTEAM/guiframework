#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QString>
#include <QList>

enum MeasureMode {
    REST,
    ACTIVITY
};

class DataReceiver
{
    // avoid object creation:
    DataReceiver();
    DataReceiver(const DataReceiver&);
    const DataReceiver& operator=(const DataReceiver&);

    // private statics:
    static void handleUserData(const QString&);
    static void handleSensorData(const QString&);

public:
    static bool validateData();
};

#endif // DATARECEIVER_H

