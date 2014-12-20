#include "selectioncontroller.h"


SelectionController::SelectionController(QObject* aParent,
                                         SelectionModel& aYearModel,
                                         SelectionModel& aMonthModel,
                                         SelectionModel& aWeekModel,
                                         SensorModel& aInactiveModel):   QObject(aParent),
                                                                         m_yearModel(aYearModel),
                                                                         m_monthModel(aMonthModel),
                                                                         m_weekModel(aWeekModel),
                                                                         m_inactiveSensorModel(aInactiveModel)
{
    //C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("cmbSelectYearFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(activated(int)), this, SLOT(selectYearSlot(int)));
        }
        child = aParent->findChild<QObject*>("cmbSelectMonthFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(activated(int)), this, SLOT(selectMonthSlot(int)));
        }
        child = aParent->findChild<QObject*>("cmbSelectWeekFilterName");
        if(child)
        {
            QObject::connect(child, SIGNAL(activated(int)), this, SLOT(selectWeekSlot(int)));
        }
    }
    else qDebug() << "Signal could not attached to a slot";
}

void SelectionController::selectYearSlot(int aIndex)
{
    qDebug() << "selectYearSlot";
    qDebug() << "Current Index = " << aIndex;

    QList<QString> selectionMonthData;
    selectionMonthData.append("Januar");
    selectionMonthData.append("März");
    selectionMonthData.append("Juni");
    selectionMonthData.append("Juli");
    selectionMonthData.append("Dezember");

    m_monthModel.setNewSelectionModel(selectionMonthData);
}

void SelectionController::selectMonthSlot(int aIndex)
{
    qDebug() << "selectMonthSlot";
    qDebug() << "Current Index = " << aIndex;

    QList<QString> selectionWeekData;
    selectionWeekData.append("1");
    selectionWeekData.append("2");
    selectionWeekData.append("3");
    selectionWeekData.append("4");

    m_weekModel.setNewSelectionModel(selectionWeekData);
}

void SelectionController::selectWeekSlot(int aIndex)
{
    qDebug() << "selectWeekSlot";
    qDebug() << "Current Index = " << aIndex;

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

    m_inactiveSensorModel.setNewSensorModel(sensorDataI);
}
