//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   tableselectioncontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   22.12.2014 10:30:00 GMT
  *
  * @brief  Include all declarations from TableSelectionController
  *
  */

#ifndef TABLESELECTIONCONTROLLER_H
#define TABLESELECTIONCONTROLLER_H

#include <QObject>
#include "Model/sensormodel.h"
#include "Model/activesensorcalcmodel.h"
#include "ImportExport/ImportExport.h"

/**
 * @brief The TableSelectionController class Manange interaction with overview table to show current run on diagram
 */
class TableSelectionController : public QObject
{
    Q_OBJECT
    public:

        /**
         * @brief TableSelectionController Constructor to init all attributes
         * @param aParent                   Pointer to QObject parent class
         * @param aRunModel                 Reference to SensorModel with a overview of single runs
         * @param aActiveSensorModel        Reference to SensorModel with active sensor data
         * @param aActiveSensorCalcModel    Reference to ActiveSensorCalcModel with calculate data
         * @param aStorage                  Reference to database to get data
         */
        TableSelectionController(QObject* aParent,
                                 SensorModel& aRunModel,
                                 SensorModel& aActiveSensorModel,
                                 ActiveSensorCalcModel& aActiveSensorCalcModel,
                                 ImportExport& aStorage);

        /**
         * @brief TableSelectionController Copy-Constructor is not allowed
         * @param aOther    Reference to a other TableSelectionController to init Object
         */
        TableSelectionController(const TableSelectionController& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        TableSelectionController& operator= (const TableSelectionController& aRhs) = delete;

    public slots:

        /**
         * @brief selectSingleRunSlot Slot to get all data from a selected run
         * @param aIndex    Index of model
         */
        void selectSingleRunSlot(int aIndex);

    private:

        /**
         * @brief m_runModel SensorModel with a overview of runs
         */
        SensorModel& m_runModel;

        /**
         * @brief m_activeSensorModel SensorModel with active sensor data from a single run
         */
        SensorModel& m_activeSensorModel;

        /**
         * @brief m_activeSensorCalcModel ActiveSensorCalcModel with the calculate data
         */
        ActiveSensorCalcModel& m_activeSensorCalcModel;

        /**
         * @brief m_importExportStorage Reference with all querys to get data from database
         */
        ImportExport& m_importExportStorage;

        /**
         * @brief updateGuiWithCurrentData Update model and view with data from database and repaint diagrams
         */
        void updateGuiWithCurrentData();
};

#endif // TABLESELECTIONCONTROLLER_H
