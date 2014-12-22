//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   filtercontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include <QObject>
#include "Model/sensormodel.h"
#include "Model/inactivesensorcalcmodel.h"
#include "ImportExport/ImportExport.h"
#include <QDate>

class FilterController : public QObject
{
    Q_OBJECT
    public:

        FilterController(QObject* aParent, SensorModel& aModel, InactiveSensorCalcModel& aCalcModel, ImportExport& aStorage);

    public slots:

        void validateUserInputSlot();

    private:

        SensorModel& m_inactiveSensorModel;

        InactiveSensorCalcModel& m_inactiveCalcModel;

        ImportExport& m_importExportStorgae;

        void updateGuiWithCurrentData();

        void setAllAvailableDataFromStorage();
};

#endif // FILTERCONTROLLER_H
