#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QString>
#include <QList>

class DataReceiver
{
    // avoid object creation:
    DataReceiver();
    DataReceiver(const DataReceiver&);
    const DataReceiver& operator=(const DataReceiver&);

    // private statics:
    static void handleUserData(const QString&);
    static void handleSensorData(const QString&);

    // private data structures
    enum DataTypes {
        MODE = 0x00,
        MOOD = 0x01,
        DATA = 0xff
    };

    enum MeasureMode {
        REST,
        ACTIVITY
    };

    enum Mood {
        GOOD = 0x00,
        AVG = 0x01,
        BAD = 0x02,
    };

    struct Data {
        qint32 timestamp;
        qint16 heartrate;
        qint16 steps;
    };

public:
    static bool validateData();
};

#endif // DATARECEIVER_H

