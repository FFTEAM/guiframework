//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   filtercontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   21.12.2014 13:13:05 GMT
  *
  * @brief  Implementation file of FilterController class
  *
  */

#include "filtercontroller.h"

FilterController::FilterController(QObject* aParent,
                                   SensorModel& aModel,
                                   InactiveSensorCalcModel& aCalcModel,
                                   ImportExport& aStorage) : QObject(aParent),
                                                             m_inactiveSensorModel(aModel),
                                                             m_inactiveCalcModel(aCalcModel),
                                                             m_importExportStorage(aStorage)
{
    // C'tor
    if(aParent)
    {
        QObject* child = aParent->findChild<QObject*>("filerButtonName");
        if(child)
        {
            connect(child,SIGNAL(clicked()), this, SLOT(validateUserInputSlot()));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";

    setAllAvailableDataFromStorage();
    updateGuiWithCurrentData();
}

void FilterController::validateUserInputSlot()
{
    const QString inputStartDate    = parent()->findChild<QObject*>("startDateInputName")->property("text").toString();
    const QString inputEndDate      = parent()->findChild<QObject*>("endDateInputName")->property("text").toString();

    if(inputStartDate.size() == 0 and inputEndDate.size() == 0)
    {
        setAllAvailableDataFromStorage();
        updateGuiWithCurrentData();
    }
    else
    {
        QDate startDate = QDate::fromString(inputStartDate, "dd-MM-yyyy");
        QDate endDate   = QDate::fromString(inputEndDate, "dd-MM-yyyy");

        if(startDate.isValid() == true && endDate.isValid() == true)
        {
            QObject* errorLabel = parent()->findChild<QObject*>("errorLabelName");
            if(errorLabel)
            {
                if(!errorLabel->property("text").toString().isEmpty())
                {
                    errorLabel->setProperty("text","");
                }
            }
            else qDebug() << "No errorLabel";

            // Get data from filter settings
            QList<const SensorData*> dataList = m_importExportStorage.measurementsFromTo(1, startDate, endDate);

            // Update Model
            m_inactiveSensorModel.setNewSensorModel(dataList);
            m_inactiveCalcModel.updateCalcValues(m_inactiveSensorModel);

            updateGuiWithCurrentData();
        }
        else
        {
            if(startDate.isValid() == false && endDate.isValid() == true)
            {
                QObject* errorLabel = parent()->findChild<QObject*>("errorLabelName");
                if(errorLabel)
                {
                    errorLabel->setProperty("text",tr("invalid start date  "));
                }
                else qDebug() << "No errorLabel";
            }
            else
            {
                if(endDate.isValid() == false && startDate.isValid() == true)
                {
                    QObject* errorLabel = parent()->findChild<QObject*>("errorLabelName");
                    if(errorLabel)
                    {
                        errorLabel->setProperty("text",tr("invalid end date  "));
                    }
                    else qDebug() << "No errorLabel";
                }
                else
                {
                    QObject* errorLabel = parent()->findChild<QObject*>("errorLabelName");
                    if(errorLabel)
                    {
                        errorLabel->setProperty("text",tr("invalid start date / end date  "));
                    }
                    else qDebug() << "No errorLabel";
                }
            }
        }
    }
}

void FilterController::updateGuiWithCurrentData()
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

void FilterController::setAllAvailableDataFromStorage()
{
    // Get all available data from storage
    QList<const SensorData*> allData = m_importExportStorage.measurements(1);

    // Update Model
    m_inactiveSensorModel.setNewSensorModel(allData);
    m_inactiveCalcModel.updateCalcValues(m_inactiveSensorModel);
}
