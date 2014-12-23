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
  * @brief  Include all declarations from Filtercontroller
  *
  */

#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include <QObject>
#include "Model/sensormodel.h"
#include "Model/inactivesensorcalcmodel.h"
#include "ImportExport/ImportExport.h"
#include <QDate>

/**
 * @brief The FilterController class Manage all filter interaction from view
 */
class FilterController : public QObject
{
    Q_OBJECT
    public:

        /**
         * @brief FilterController Constructor Init all attributes on class
         * @param aParent       Pointer to QObject parent class
         * @param aModel        Reference to a SensorModel
         * @param aCalcModel    Reference to a InactiveSensorCalcModel
         * @param aStorage      Reference to database with data to update model and view
         */
        FilterController(QObject* aParent, SensorModel& aModel, InactiveSensorCalcModel& aCalcModel, ImportExport& aStorage);

        /**
         * @brief FilterController Copy-Constructor is not allowed
         * @param aOther    Reference to a other FilterController to init Object
         */
        FilterController(const FilterController& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        FilterController& operator= (const FilterController& aRhs) = delete;

    public slots:

        /**
         * @brief validateUserInputSlot Slot to validate given user input
         */
        void validateUserInputSlot();

    private:

        /**
         * @brief m_inactiveSensorModel SensorModel to store data and update view
         */
        SensorModel& m_inactiveSensorModel;

        /**
         * @brief m_inactiveCalcModel InactiveSensorCalcModel to store calculate data and update view
         */
        InactiveSensorCalcModel& m_inactiveCalcModel;

        /**
         * @brief m_importExportStorgae ImportExport reference with query to get data from database
         */
        ImportExport& m_importExportStorage;

        /**
         * @brief updateGuiWithCurrentData Update model and diagrams on view
         */
        void updateGuiWithCurrentData();

        /**
         * @brief setAllAvailableDataFromStorage Set all available data from database
         */
        void setAllAvailableDataFromStorage();
};

#endif // FILTERCONTROLLER_H
