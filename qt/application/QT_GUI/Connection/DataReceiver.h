#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QString>
#include <QList>
#include <QObject>

#include "Model/Data/sensordata.h"

struct rawData {
    quint64 timeStamp;
    quint16 heartRate;
    quint16 steps;
};

class DataReceiver : public QObject
{
    Q_OBJECT
    static DataReceiver* mInstance;

    // avoid object creation:
    explicit DataReceiver(QObject *parent = 0);
    explicit DataReceiver(const DataReceiver&);
    const DataReceiver& operator=(const DataReceiver&);

    // private data structures
    enum STATEMACHINE {
        MODE_STATE,
        MOOD_STATE,
        AVGR_STATE,
        DATA_STATE,
        FINAL_STATE
    };

    enum DataTypes {
        MODE = 0x00,
        MOOD = 0x01,
        AVGR = 0x02,
        DATA = 0xff
    };

signals:
    void updateStorage(QList<rawData>&, quint8, quint8, quint16);
    void signalizeController(quint8);

public:
    static DataReceiver& getInstance();
    bool validateData(const quint8 *, const quint64 aLen);
};

#endif // DATARECEIVER_H

