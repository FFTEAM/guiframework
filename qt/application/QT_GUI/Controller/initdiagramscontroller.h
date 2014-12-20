#ifndef INITDIAGRAMSCONTROLLER_H
#define INITDIAGRAMSCONTROLLER_H

#include <QObject>
#include <Model/sensormodel.h>

class InitDiagramsController: public QObject
{
    Q_OBJECT
    public:

        InitDiagramsController(QObject* aParent, SensorModel& aInactiveModel, SensorModel& aActiveModel);

    private:

        void updateGuiWithCurrentData();

        SensorModel& m_inactiveModel;
        SensorModel& m_activeModel;
};

#endif // INITDIAGRAMSCONTROLLER_H
