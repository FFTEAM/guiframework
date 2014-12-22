//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selectioncontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef SELECTIONCONTROLLER_H
#define SELECTIONCONTROLLER_H

#include <QObject>
#include "Model/selectionmodel.h"
#include "Model/sensormodel.h"
#include "ImportExport/ImportExport.h"

class SelectionController: public QObject
{
    Q_OBJECT
    public:

        /**
         * @brief SelectionController   Constructor
         * @param aParent               Parent
         * @param aYearModel            Reference to Year Model
         * @param aMonthModel           Reference to Month Model
         * @param aWeekModel            Reference to Week Model
         */
        SelectionController(QObject* aParent,
                            SelectionModel& aYearModel,
                            SelectionModel& aMonthModel,
                            SelectionModel& aWeekModel,
                            SensorModel& aInactiveModel,
                            SensorModel& aRunModel,
                            ImportExport& aStorage);

    public slots:

        /**
         * @brief selectYearSlot Slot to get current year from view
         * @param aCurrentText current text of combobox
         */
        void selectYearSlot(QString aCurrentText);

        /**
         * @brief selectMonthSlot Slot to get current month from view
         * @param aIndex current index of combobox
         */
        void selectMonthSlot(QString aCurrentText);

        /**
         * @brief selectWeekSlot Slot to get current week from view
         * @param aIndex current index of combobox
         */
        void selectWeekSlot(QString aCurrentText);

    private:

        /**
         * @brief m_currentText String with the current year of combobox
         */
        QString m_currentText;

        /**
         * @brief m_yearModel hold the available year values
         */
        SelectionModel& m_yearModel;

        /**
         * @brief m_monthModel hold the available month values
         */
        SelectionModel& m_monthModel;

        /**
         * @brief m_weekModel hold the available week values
         */
        SelectionModel& m_weekModel;

        /**
         * @brief m_inactiveSensorModel hold the current inactiveSensorModel
         */
        SensorModel& m_sensorModel;

        SensorModel& m_runModel;

        ImportExport& m_importExportStorage;

};

#endif // SELECTIONCONTROLLER_H
