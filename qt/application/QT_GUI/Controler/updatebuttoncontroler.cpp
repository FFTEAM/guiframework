#include "updatebuttoncontroler.h"

UpdateButtonControler::UpdateButtonControler(QObject *aParent, SensorModel* aModel) :   QObject(aParent),
                                                                                        m_SensorList(aModel)
{
    //C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("updateActionName");
        if(child)
        {
            QObject::connect(child, SIGNAL(updateActionIsTriggered()), this, SLOT(updateActionSlot()));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void UpdateButtonControler::updateActionSlot()
{
    qDebug() << "updateActionSlot called";
    if(m_SensorList)
    {
        QObject* inactiveDiagram = parent()->findChild<QObject*>("inactiveDiagramName");
        QObject* activeDiagram = parent()->findChild<QObject*>("activeDiagramName");

        if(inactiveDiagram && activeDiagram)
        {
            inactiveDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
            activeDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
        }
        else qDebug() << "No childs found";

        QList<SensorData> sensorData;
        sensorData.append(SensorData("01-01-2015 00:00:01","200","5"));
        sensorData.append(SensorData("01-01-2015 00:00:02","100","3"));
        sensorData.append(SensorData("01-01-2015 00:00:02","50","3"));
        SensorModel::getInstance().setNewSensorModel(sensorData);

        if(inactiveDiagram && activeDiagram)
        {
            inactiveDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
            activeDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Null pointer";
}
