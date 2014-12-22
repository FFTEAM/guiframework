//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   filtercontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "filtercontroller.h"

FilterController::FilterController(QObject* aParent,
                                   SensorModel& aModel,
                                   InactiveSensorCalcModel& aCalcModel) : QObject(aParent),
                                                                         m_inactiveSensorModel(aModel),
                                                                         m_inactiveCalcModel(aCalcModel)
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
}

void FilterController::validateUserInputSlot()
{
    const QString inputStartDate    = parent()->findChild<QObject*>("startDateInputName")->property("text").toString();
    const QString inputEndDate      = parent()->findChild<QObject*>("endDateInputName")->property("text").toString();

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

        // ToDo query to database with current dates to get QList for model

        // EXAMPLE DATA:
        QList<const SensorData*> sensorDataI;
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5, 7));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 8));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3, 9));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 210, 5, 11));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 22));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3, 11));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5, 22));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3, 11));
        sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 10, 3, 22));

        m_inactiveSensorModel.setNewSensorModel(sensorDataI);
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
