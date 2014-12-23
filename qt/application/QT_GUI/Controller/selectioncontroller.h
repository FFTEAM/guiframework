//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selectioncontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   20.12.2014 11:56:00 GMT
  *
  * @brief  Include all declarations from SelectionController
  *
  */

#ifndef SELECTIONCONTROLLER_H
#define SELECTIONCONTROLLER_H

#include <QObject>
#include "Model/selectionmodel.h"
#include "Model/sensormodel.h"
#include "Model/activesensorcalcmodel.h"
#include "ImportExport/ImportExport.h"

/**
 * @brief The SelectionController class This calss manage the interaction with the comboboxes on "inactive" Tab
 */
class SelectionController: public QObject
{
    Q_OBJECT
    public:

        /**
         * @brief SelectionController   Constructor to init all attributes
         * @param aParent               Pointer to QObject parent calss
         * @param aYearModel            Reference to SelectionModel with data for year combobox
         * @param aMonthModel           Reference to SelectionModel with data for month combobox
         * @param aInactiveModel        Reference to SensorModel with all inactive sensor data
         * @param aRunModel             Reference to SensorModel with a overview of all actvie sensor data
         * @param aCalcModel            Reference to SensorCalcModel with all calculate actvie sensor data
         * @param aStorage              Reference with all querys to get data from database
         */
        SelectionController(QObject* aParent,
                            SelectionModel& aYearModel,
                            SelectionModel& aMonthModel,
                            SensorModel& aInactiveModel,
                            SensorModel& aRunModel,
                            ActiveSensorCalcModel& aCalcModel,
                            ImportExport& aStorage);

        /**
         * @brief SelectionController Copy-Constructor is not allowed
         * @param aOther    Reference to a other SelectionController to init Object
         */
        SelectionController(const SelectionController& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        SelectionController& operator= (const SelectionController& aRhs) = delete;

    public slots:

        /**
         * @brief selectYearSlot Slot to get current year from view
         * @param aCurrentText Selected text from year combobox
         */
        void selectYearSlot(QString aCurrentText);

        /**
         * @brief selectMonthSlot Slot to get current month from view
         * @param aIndex Selected text from month combobox
         */
        void selectMonthSlot(QString aCurrentText);

    private:

        /**
         * @brief setAllAvailableData Set all available active sensor data from database to models
         */
        void setAllAvailableData();

        /**
         * @brief setAllAvailableYearData Set all available actvie data from a selected year to models
         * @param aCurrentText Text with the selected year
         */
        void setAllAvailableYearData(QString aCurrentText);

        /**
         * @brief updateGuiWithCurrentData Update model and view with data from database and repaint diagrams
         */
        void updateGuiWithCurrentData();

        /**
         * @brief m_currentText String with the current year of combobox
         */
        QString m_currentYearText;

        /**
         * @brief m_currentMonthText String with the current month of combobox
         */
        QString m_currentMonthText;

        /**
         * @brief m_yearModel SelectionModel with values for year combobox
         */
        SelectionModel& m_yearModel;

        /**
         * @brief m_monthModel SelectionModel with values for month combobox
         */
        SelectionModel& m_monthModel;

        /**
         * @brief m_inactiveSensorModel SensorModel with active data from database
         */
        SensorModel& m_sensorModel;

        /**
         * @brief m_runModel SensorModel with a overview of single runs from database
         */
        SensorModel& m_runModel;

        /**
         * @brief m_activeCalcModel ActiveSensorCalcModel with the current calculate datas
         */
        ActiveSensorCalcModel& m_activeCalcModel;

        /**
         * @brief m_importExportStorgae ImportExport reference with query to get data from database
         */
        ImportExport& m_importExportStorage;

};

#endif // SELECTIONCONTROLLER_H
