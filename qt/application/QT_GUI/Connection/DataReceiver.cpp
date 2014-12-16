#include "DataReceiver.h"

#include <QDebug>
#include <QUrlQuery>

bool DataReceiver::validateData()
{
    /*measure_mode=activity
    1418651612;0;0
    1418651615;0;9
    1418651618;0;20
    1418651621;90;33
    1418651624;88;40
    1418651627;86;50
    1418651630;91;53
    1418651633;95;65*/

    //if (0 < aMsgBlock.size())
    {
        // parse first line:
        //QUrlQuery query(aMsgBlock[0]);
        //query.setQueryDelimiters('=', ';');
        //QStringList strList = query.allQueryItemValues("measure_mode");

        return true;
    }

    return false;
}

void DataReceiver::handleUserData(const QString&)
{

}

void DataReceiver::handleSensorData(const QString&)
{

}
