//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   updatebuttoncontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 14:12:00 GMT
  *
  * @brief Diese CPP-Datei enthält alle Implementierung der Methoden der Klasse UpdateButtonController
  *
  */

#include "updatebuttoncontroller.h"

UpdateButtonController::UpdateButtonController(QObject *aParent) :   QObject(aParent)
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

void UpdateButtonController::updateActionSlot()
{
    qDebug() << "updateActionSlot called";

    QObject* inactiveDiagram = parent()->findChild<QObject*>("inactiveDiagramName");
    QObject* activeDiagram = parent()->findChild<QObject*>("activeDiagramName");

    if(inactiveDiagram && activeDiagram)
    {
        inactiveDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
        activeDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
    }
    else qDebug() << "No childs found";

    // EXAMPLE DATA:
    QList<const SensorData*> sensorDataI;

    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3));

    QList<const SensorData*> sensorDataA;
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 1)), 230, 5));
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 2)), 120, 10));
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 3)), 30, 3));

    ActiveSensorModel::getInstance().setNewSensorModel(sensorDataA);
    ActiveSensorCalcModel::getInstance().updateCalcValues(ActiveSensorModel::getInstance());

    InactiveSensorModel::getInstance().setNewSensorModel(sensorDataI);
    InactiveSensorCalcModel::getInstance().updateCalcValues(InactiveSensorModel::getInstance());

    if(inactiveDiagram && activeDiagram)
    {
        inactiveDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
        activeDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
    }
    else qDebug() << "No child found";
}
