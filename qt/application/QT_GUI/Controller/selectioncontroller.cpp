#include "selectioncontroller.h"


SelectionController::SelectionController(QObject* aParent,
                                         SelectionModel& aYearModel,
                                         SelectionModel& aMonthModel,
                                         SelectionModel& aWeekModel): QObject(aParent),
                                                                      m_yearModel(aYearModel),
                                                                      m_monthModel(aMonthModel),
                                                                      m_weekModel(aWeekModel)
{
    // C'tor
}

void SelectionController::selectYearSlot(QString aYear)
{

}

void SelectionController::selectMonthSlot(QString aMonth)
{

}

void SelectionController::selectWeekSlot(QString aWeek)
{

}
