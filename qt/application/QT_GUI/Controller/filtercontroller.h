#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include <QObject>
#include "Model/sensormodel.h"
#include "Model/inactivesensorcalcmodel.h"
#include <QDate>

class FilterController : public QObject
{
    Q_OBJECT
    public:

        FilterController(QObject* aParent, SensorModel& aModel, InactiveSensorCalcModel& aCalcModel);

    public slots:

        void validateUserInputSlot();

    private:



        SensorModel& m_inactiveSensorModel;

        InactiveSensorCalcModel& m_inactiveCalcModel;

        void updateGuiWithCurrentData();
};

#endif // FILTERCONTROLLER_H
