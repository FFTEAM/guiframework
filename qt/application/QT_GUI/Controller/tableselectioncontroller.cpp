#include "tableselectioncontroller.h"

TableSelectionController::TableSelectionController(QObject* aParent,
                                                   SensorModel& aRunModel,
                                                   SensorModel& aActiveSensorModel,
                                                   ActiveSensorCalcModel& aActiveSensorCalcModel,
                                                   ImportExport& aStorage): QObject(aParent),
                                                                            m_runModel(aRunModel),
                                                                            m_activeSensorModel(aActiveSensorModel),
                                                                            m_activeSensorCalcModel(aActiveSensorCalcModel),
                                                                            m_importExportStorage(aStorage)
{
    // C'tor
    if(aParent)
    {
        QObject* child = aParent->findChild<QObject*>("tableRunName");
        if(child)
        {
            connect(child,SIGNAL(clicked(int)), this, SLOT(selectSingleRunSlot(int)));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void TableSelectionController::selectSingleRunSlot(int aIndex)
{
    qDebug() << "selectSingleRunSlot called" << aIndex;
    const SensorData* singleData =  m_runModel.getSingleSensorData(aIndex);
    const int id = singleData->getId();

    // call storage for measurements with current id
    QList<const SensorData*> dataList = m_importExportStorage.dataByMeasurementId(id);

    // update models
    m_activeSensorModel.setNewSensorModel(dataList);
    m_activeSensorCalcModel.updateCalcValues(m_activeSensorModel);
    updateGuiWithCurrentData();
}

void TableSelectionController::updateGuiWithCurrentData()
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
