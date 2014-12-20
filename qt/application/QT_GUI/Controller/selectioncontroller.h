#ifndef SELECTIONCONTROLLER_H
#define SELECTIONCONTROLLER_H

#include <QObject>
#include "Model/selectionmodel.h"

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
        SelectionController(QObject* aParent, SelectionModel& aYearModel, SelectionModel& aMonthModel, SelectionModel& aWeekModel);

    public slots:

        /**
         * @brief selectYearSlot Slot to get current year from view
         * @param aYear current year select on view
         */
        void selectYearSlot(QString aYear);

        /**
         * @brief selectMonthSlot Slot to get current month from view
         * @param aMonth current month select on view
         */
        void selectMonthSlot(QString aMonth);

        /**
         * @brief selectWeekSlot Slot to get current week from view
         * @param aWeek current week select on view
         */
        void selectWeekSlot(QString aWeek);

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
};

#endif // SELECTIONCONTROLLER_H
