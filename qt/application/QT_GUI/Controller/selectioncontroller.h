#ifndef SELECTIONCONTROLLER_H
#define SELECTIONCONTROLLER_H

#include <QObject>
#include "Model/selectionmodel.h"
#include "Model/sensormodel.h"

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
        SelectionController(QObject* aParent, SelectionModel& aYearModel, SelectionModel& aMonthModel, SelectionModel& aWeekModel, SensorModel& aInactiveModel);

    public slots:

        /**
         * @brief selectYearSlot Slot to get current year from view
         * @param aIndex current index of combobox
         */
        void selectYearSlot(int aIndex);

        /**
         * @brief selectMonthSlot Slot to get current month from view
         * @param aIndex current index of combobox
         */
        void selectMonthSlot(int aIndex);

        /**
         * @brief selectWeekSlot Slot to get current week from view
         * @param aIndex current index of combobox
         */
        void selectWeekSlot(int aIndex);

    private:

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
        SensorModel& m_inactiveSensorModel;
};

#endif // SELECTIONCONTROLLER_H
