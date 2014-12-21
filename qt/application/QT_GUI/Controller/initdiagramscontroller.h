//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   initdiagramcontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

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
