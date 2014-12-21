//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   initdiagramscontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "initdiagramscontroller.h"

InitDiagramsController::InitDiagramsController(QObject *aParent,
                                               SensorModel &aInactiveModel,
                                               SensorModel &aActiveModel): QObject(aParent),
                                                                           m_inactiveModel(aInactiveModel),
                                                                           m_activeModel(aActiveModel)
{
    // C'tor
    aParent->findChild<QObject*>("inactiveDiagramName")->setProperty("data",QVariant::fromValue(&m_inactiveModel));
    aParent->findChild<QObject*>("activeDiagramName")->setProperty("data",QVariant::fromValue(&m_activeModel));
    updateGuiWithCurrentData();
}

void InitDiagramsController::updateGuiWithCurrentData()
{
    QObject* inactiveDiagram = parent()->findChild<QObject*>("inactiveDiagramName");
    QObject* activeDiagram = parent()->findChild<QObject*>("activeDiagramName");

    if(inactiveDiagram && activeDiagram)
    {
        inactiveDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
        activeDiagram->setProperty("state","BEGIN_UPDATE_DIAGRAMM");
    }
    else qDebug() << "No childs found";

    if(inactiveDiagram && activeDiagram)
    {
        inactiveDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
        activeDiagram->setProperty("state","END_UPDATE_DIAGRAMM");
    }
    else qDebug() << "No child found";
}
