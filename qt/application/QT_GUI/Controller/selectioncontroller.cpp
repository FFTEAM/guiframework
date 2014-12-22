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
                                         SensorModel& aInactiveModel,
                                         SensorModel& aRunModel,
                                         ImportExport& aStorage):   QObject(aParent),
                                                                    m_currentText(""),
                                                                    m_yearModel(aYearModel),
                                                                    m_monthModel(aMonthModel),
                                                                    m_weekModel(aWeekModel),
                                                                    m_sensorModel(aInactiveModel),
                                                                    m_runModel(aRunModel),
                                                                    m_importExportStorage(aStorage)
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

    // get all possible years in storage
    QList<QString> dataList = m_importExportStorage.years(0);
    dataList.push_front("all");
    m_yearModel.setNewSelectionModel(dataList);

    // set run model
}

void SelectionController::selectYearSlot(QString aCurrentText)
{
    if(m_currentText.compare(aCurrentText) != 0)
    {
        m_currentText = aCurrentText;

        if(0 == m_currentText.compare("all"))
        {
            // read all informations from storage
            QObject* child = parent()->findChild<QObject*>("yearRectName");
            if(child)
            {
                child->setProperty("state", "BEGIN_SELECTION");
                qDebug() << "State change to BEGIN_SELECTION";
            }
            else qDebug() << "No state change";
        }
        else
        {
            // get all possible month from storage
            // update model

            QObject* child = parent()->findChild<QObject*>("yearRectName");
            if(child)
            {
                child->setProperty("state", "BEGIN_SELECTION_MONTH");
                qDebug() << "State change to BEGIN_SELECTION_MONTH";
            }

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
}

void SelectionController::selectMonthSlot(QString aCurrentText)
{
//    QList<QString> selectionWeekData;
//    selectionWeekData.append("1");
//    selectionWeekData.append("2");
//    selectionWeekData.append("3");
//    selectionWeekData.append("4");

//    m_weekModel.setNewSelectionModel(selectionWeekData);
}

void SelectionController::selectWeekSlot(QString aCurrentText)
{
//    // EXAMPLE DATA:
//    QList<const SensorData*> sensorDataI;
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5, 1));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 2));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3, 3));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5, 4));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 5));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3, 6));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5, 7));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 8));
//    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3, 9));

//    m_sensorModel.setNewSensorModel(sensorDataI);
}
