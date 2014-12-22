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
                                         ActiveSensorCalcModel& aCalcModel,
                                         ImportExport& aStorage):   QObject(aParent),
                                                                    m_currentYearText(""),
                                                                    m_currentMonthText(""),
                                                                    m_yearModel(aYearModel),
                                                                    m_monthModel(aMonthModel),
                                                                    m_weekModel(aWeekModel),
                                                                    m_sensorModel(aInactiveModel),
                                                                    m_runModel(aRunModel),
                                                                    m_activeCalcModel(aCalcModel),
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
    dataList.push_front(tr("all"));

    // set combobox
    m_yearModel.setNewSelectionModel(dataList);

    setAllAvailableData();
}

void SelectionController::selectYearSlot(QString aCurrentText)
{
    if(m_currentYearText.compare(aCurrentText) != 0)
    {
        m_currentYearText = aCurrentText;

        if(0 == m_currentYearText.compare("all"))
        {
            // read all informations from storage
            QObject* monthChild = parent()->findChild<QObject*>("monthRectName");
            QObject* weekChild = parent()->findChild<QObject*>("weekRectName");
            if(monthChild && weekChild)
            {
                monthChild->setProperty("visible", "false");
                weekChild->setProperty("visible", "false");
                setAllAvailableData();
            }
            else qDebug() << "No state change";
        }
        else
        {
            // get all possible month from storage
            QList<QString> selectionMonthData = m_importExportStorage.months(0, QDate::fromString(aCurrentText, "yyyy"));
            selectionMonthData.push_front(tr("all"));
            m_monthModel.setNewSelectionModel(selectionMonthData);

            // set new model
            QDate startDate = QDate::fromString(aCurrentText, "yyyy");
            QDate endDate = QDate::fromString(aCurrentText, "yyyy").addYears(1);
            QList<const SensorData*> dataList = m_importExportStorage.measurementsFromTo(0, startDate, endDate);

            m_runModel.setNewSensorModel(dataList);

            if(m_runModel.getSensorModelCount() != 0)
            {
                const SensorData* data = m_runModel.getSingleSensorData(0);
                if(data)
                {
                    const int id = data->getId();
                    QList<const SensorData*> singleDataList = m_importExportStorage.dataByMeasurementId(id);
                    m_sensorModel.setNewSensorModel(singleDataList);
                    m_activeCalcModel.updateCalcValues(m_sensorModel);
                }
                else
                {
                    qDebug() << "Error no new model set";
                }
            }
            else
            {
                QList<const SensorData*> emptyVector;
                m_sensorModel.setNewSensorModel(emptyVector);
                m_activeCalcModel.updateCalcValues(m_sensorModel);
            }
            updateGuiWithCurrentData();

            QObject* child = parent()->findChild<QObject*>("monthRectName");
            if(child)
            {
                child->setProperty("visible", "true");
            }
        }
    }
}

void SelectionController::selectMonthSlot(QString aCurrentText)
{
    if(m_currentMonthText.compare(aCurrentText) != 0)
    {
        m_currentMonthText = aCurrentText;

        if(0 == m_currentMonthText.compare("all"))
        {
            // read all informations from storage
            QObject* weekChild = parent()->findChild<QObject*>("weekRectName");
            if(weekChild)
            {
                weekChild->setProperty("visible", "false");
                // get all data from month
            }
            else qDebug() << "No state change";
        }
        else
        {
            QList<QString> weekList = m_importExportStorage.weeks(0,QDate::fromString(m_currentYearText, "yyyy"),QDate::fromString(m_currentMonthText, "MMMM"));
            m_weekModel.setNewSelectionModel(weekList);
            QObject* child = parent()->findChild<QObject*>("weekRectName");
            if(child)
            {
                child->setProperty("visible", "true");
            }
        }
    }

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

void SelectionController::setAllAvailableData()
{
    // set table with runs
    QList<const SensorData*> sensorList = m_importExportStorage.measurements(0);
    m_runModel.setNewSensorModel(sensorList);

    if(m_runModel.getSensorModelCount() != 0)
    {
        const SensorData* data = m_runModel.getSingleSensorData(0);
        if(data)
        {
            const int id = data->getId();
            QList<const SensorData*> singleDataList = m_importExportStorage.dataByMeasurementId(id);
            m_sensorModel.setNewSensorModel(singleDataList);
            m_activeCalcModel.updateCalcValues(m_sensorModel);
        }
        else
        {
            qDebug() << "Error no new model set";
        }
    }
    else
    {
        QList<const SensorData*> emptyVector;
        m_sensorModel.setNewSensorModel(emptyVector);
        m_activeCalcModel.updateCalcValues(m_sensorModel);
    }
    updateGuiWithCurrentData();
}

void SelectionController::updateGuiWithCurrentData()
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
