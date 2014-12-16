#include "DataReceiver.h"
#include "Model/Data/sensordata.h"

#include <QDebug>
#include <QList>
#include <QDateTime>
#include <QUrlQuery>
#include <QtEndian>

bool DataReceiver::validateData(const unsigned char* aData, qint64 aLen)
{
    qint64 pos = 0;
    unsigned char mode, mood;
    QList<const SensorData*> sensorData;

    do
    {
        // switch through datatypes:
        switch (aData[pos])
        {
            case MODE:
                qDebug("MODE data packet found");
                mode = aData[pos+1];
                pos += 2;
            break;

            case MOOD:
                qDebug("MOOD data packet found");
                mood = aData[pos+1];
                pos += 2;
            break;

            case DATA:
            {
                qDebug("DATA data packet found");
                pos++;
                quint64 timeStampMs;
                quint16 heartRate, steps;

                memcpy(&timeStampMs, aData+pos, 8); pos += 8;
                memcpy(&heartRate, aData+pos, 2); pos += 2;
                memcpy(&steps    , aData+pos, 2); pos += 2;

                // rewind network byte order:
                timeStampMs = qFromBigEndian(timeStampMs);
                heartRate = qFromBigEndian(heartRate);
                steps = qFromBigEndian(steps);

                QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(timeStampMs);
                sensorData.append(new SensorData(dateTime, heartRate, steps));
            }
            break;

            default:
                qFatal("invalid datatype!");
            return false;
        }

    } while (pos < aLen);

    return false;
}

void DataReceiver::handleUserData(const QString&)
{

}

void DataReceiver::handleSensorData(const QString&)
{

}
