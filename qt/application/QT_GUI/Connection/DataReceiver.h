//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   DataReceiver.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of DataReceiver
  *
  */

#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QString>
#include <QList>
#include <QObject>

#include "Model/Data/sensordata.h"

/**
 * @struct rawData
 * @brief simple data structure for received measurement datapoints
 *
 * is used for building a list containing all measurement values for a measurement.
 * this list is used by ImportExport class
 */
struct rawData {
    quint64 timeStamp;
    quint16 heartRate;
    quint16 steps;
};

/**
 * @class DataReceiver
 * @brief Implements the parser for incoming measurements
 *
 * Is implemented as singleton class and used for parsing the received byte-vector.
 * On successful parsing, the list of parsed measurement information is passed to ImportExport-class
 */
class DataReceiver final : public QObject
{
    Q_OBJECT

    /**
     * @brief mInstance is holding the single instance of this class
     */
    static DataReceiver* mInstance;

    /**
     * @brief DataReceiver constructor is private due to singleton implementation
     * @param parent QObject of parent class
     */
    explicit DataReceiver(QObject *parent = 0);

    /**
     * @brief DataReceiver copy-constructor is forbidden
     */
    explicit DataReceiver(const DataReceiver&) = delete;

    /**
     * @brief operator = is forbidden
     * @return reference to current object
     */
    const DataReceiver& operator=(const DataReceiver&) = delete;

    /**
     * @enum STATEMACHINE
     * @brief The STATEMACHINE enum is defining the possible states
     */
    enum STATEMACHINE {
        MODE_STATE,
        MOOD_STATE,
        AVGR_STATE,
        DATA_STATE,
        FINAL_STATE
    };

    /**
     * @enum DataTypes
     * @brief The DataTypes enum defining the possible datatypes expected
     */
    enum DataTypes {
        MODE = 0x00,
        MOOD = 0x01,
        AVGR = 0x02,
        DATA = 0xff
    };

signals:
    /**
     * @brief updateStorage
     *
     * Is passing the parsed data to ImportExport class
     */
    void updateStorage(QList<rawData>&, quint8, quint8, quint16);

    /**
     * @brief signalizeController
     *
     * Is signalizing to the SelectionController that new data is available via ImportExport
     */
    void signalizeController(quint8);

public:
    /**
     * @brief getInstance Creation of single instance
     * @return reference to single instance
     */
    static DataReceiver& getInstance();

    /**
     * @brief validateData triggers the parsing mechanism
     * @param buffer byte-vector received by TcpConnection
     * @param aLen length of byte-vector
     * @return true on valid parsing, false on any error
     */
    bool validateData(const quint8* buffer, const quint64 aLen);
};

#endif // DATARECEIVER_H

