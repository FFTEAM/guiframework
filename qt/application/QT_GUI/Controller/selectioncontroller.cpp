//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selectioncontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "selectioncontroller.h"


SelectionController::SelectionController(QObject* aParent,
                                         SelectionModel& aYearModel,
                                         SelectionModel& aMonthModel,
                                         SelectionModel& aWeekModel,
                                         SensorModel& aInactiveModel):   QObject(aParent),
                                                                         m_yearModel(aYearModel),
                                                                         m_monthModel(aMonthModel),
                                                                         m_weekModel(aWeekModel),
                                                                         m_currentText(""),
                                                                         m_sensorModel(aInactiveModel)
{
    //C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("cmbSelectYearFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(onComboboxPressed(QString)), this, SLOT(selectYearSlot(QString)));
        }
        child = aParent->findChild<QObject*>("cmbSelectMonthFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(onComboboxPressed(QString)), this, SLOT(selectMonthSlot(QString)));
        }
        child = aParent->findChild<QObject*>("cmbSelectWeekFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(onComboboxPressed(QString)), this, SLOT(selectWeekSlot(QString)));
        }
    }
    else qDebug() << "Signal could not attached to a slot";
}

void SelectionController::selectYearSlot(QString aCurrentText)
{
    if(m_currentText.compare(aCurrentText) != 0)
    {
        m_currentText = aCurrentText;

        // ToDo read Information from database

        // Example Data
        QList<QString> selectionMonthData;
        selectionMonthData.append("Januar");
        selectionMonthData.append("März");
        selectionMonthData.append("Juni");
        selectionMonthData.append("Juli");
        selectionMonthData.append("Dezember");
        m_monthModel.setNewSelectionModel(selectionMonthData);
    }
}

void SelectionController::selectMonthSlot(QString aCurrentText)
{
    QList<QString> selectionWeekData;
    selectionWeekData.append("1");
    selectionWeekData.append("2");
    selectionWeekData.append("3");
    selectionWeekData.append("4");

    m_weekModel.setNewSelectionModel(selectionWeekData);
}

void SelectionController::selectWeekSlot(QString aCurrentText)
{
    // EXAMPLE DATA:
    QList<const SensorData*> sensorDataI;
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3));

    m_sensorModel.setNewSensorModel(sensorDataI);
}
