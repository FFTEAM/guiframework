#include "importbuttoncontroler.h"

ImportButtonControler::ImportButtonControler(QObject *aParent, SensorModel* aModel) :   QObject(aParent),
                                                                                        m_SensorList(aModel)
{
    //C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("importButton");
        if(child)
        {
            QObject::connect(child, SIGNAL(importButtonIsPressed()), this, SLOT(clickImportButtonSlot()));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void ImportButtonControler::clickImportButtonSlot()
{
    if(m_SensorList)
    {
        QList<SensorData> sensorData;
        sensorData.append(SensorData("01-01-2015 00:00:01","180","5"));
        sensorData.append(SensorData("01-01-2015 00:00:02","185","3"));
        m_SensorList->setNewSensorModel(sensorData);
    }
    else qDebug() << "Null pointer";
}
