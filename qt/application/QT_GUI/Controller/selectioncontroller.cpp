//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selectioncontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   20.12.2014 11:56:00 GMT
  *
  * @brief  Implementation file of SelectionController class
  *
  */

#include "selectioncontroller.h"


SelectionController::SelectionController(QObject* aParent,
                                         SelectionModel& aYearModel,
                                         SelectionModel& aMonthModel,
                                         SensorModel& aInactiveModel,
                                         SensorModel& aRunModel,
                                         ActiveSensorCalcModel& aCalcModel,
                                         ImportExport& aStorage):   QObject(aParent),
                                                                    m_currentYearText(""),
                                                                    m_currentMonthText(""),
                                                                    m_yearModel(aYearModel),
                                                                    m_monthModel(aMonthModel),
                                                                    m_sensorModel(aInactiveModel),
                                                                    m_runModel(aRunModel),
                                                                    m_activeCalcModel(aCalcModel),
                                                                    m_importExportStorage(aStorage)
{
    //C'tor
    connect(&DataReceiver::getInstance(), SIGNAL(signalizeController(quint8)), this, SLOT(newDataFromDeviceSlot(quint8)));

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
    }
    else qDebug() << "Signal could not attached to a slot";

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

            setAllAvailableYearData(m_currentYearText);
            updateGuiWithCurrentData();

            QObject* childRect = parent()->findChild<QObject*>("monthRectName");
            QObject* childCombobox = parent()->findChild<QObject*>("cmbSelectMonthFilterName");
            if(childRect && childCombobox)
            {
                childCombobox->setProperty("currentIndex",0);
                childRect->setProperty("visible", "true");
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
            }
            else qDebug() << "No state change";

            setAllAvailableYearData(m_currentYearText);
        }
        else
        {
            // calculate start/end Date
            int year = QDate::fromString(m_currentYearText,"yyyy").year();
            qDebug() << "Year:" <<year;
            int month = QDate::fromString(m_currentMonthText,"MMMM").month();
            qDebug() << "Month" << month;
            QDate startDate(year, month, 1);
            qDebug() << "Valid = " << startDate.isValid();
            QDate endDate(startDate);
            endDate = endDate.addMonths(1);

            // get data from storage and update model
            QList<const SensorData*> sensorList = m_importExportStorage.measurementsFromTo(0, startDate, endDate);
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
        }
        updateGuiWithCurrentData();
    }
}

void SelectionController::newDataFromDeviceSlot(quint8 aType)
{
    if(0 == aType)
    {
        QObject* selectionYear = parent()->findChild<QObject*>("cmbSelectYearFilterName");
        QObject* selectionMonth = parent()->findChild<QObject*>("cmbSelectMonthFilterName");

        if(selectionYear && selectionMonth)
        {
            QString actualYear = selectionYear->property("currentText").toString();
            m_currentYearText = "";

            if(0 == actualYear.compare("all"))
            {
                selectYearSlot(actualYear);
            }
            else
            {
                QString actualMonth = selectionYear->property("currentText").toString();
                m_currentMonthText = "";
                selectMonthSlot(actualMonth);
            }
        }
    }
}

void SelectionController::setAllAvailableData()
{
    // get all possible years in storage
    QList<QString> dataList = m_importExportStorage.years(0);
    dataList.push_front(tr("all"));

    // set combobox
    m_yearModel.setNewSelectionModel(dataList);

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

void SelectionController::setAllAvailableYearData(QString aCurrentText)
{
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
            qDebug() << "ID = "<< id;
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
