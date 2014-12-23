//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   initdiagramcontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   20.12.2014 12:54:00 GMT
  *
  * @brief  Include all declarations from InitDiagramsController
  *
  */

#ifndef INITDIAGRAMSCONTROLLER_H
#define INITDIAGRAMSCONTROLLER_H

#include <QObject>
#include <Model/sensormodel.h>

/**
 * @brief The InitDiagramsController class Init diagrams on view with actual data from database
 */
class InitDiagramsController: public QObject
{
    Q_OBJECT
    public:

        /**
         * @brief InitDiagramsController Constructor to init attributes
         * @param aParent           Pointer to QObject parent class
         * @param aInactiveModel    Reference to a SensorModel with inactive sensor data
         * @param aActiveModel      Reference to a SensorModel with active sensor data
         */
        InitDiagramsController(QObject* aParent, SensorModel& aInactiveModel, SensorModel& aActiveModel);

        /**
         * @brief InitDiagramsController Copy-Constructor is not allowed
         * @param aOther    Reference to a other InitDiagramsController to init Object
         */
        InitDiagramsController(const InitDiagramsController& aOther) = delete;

        /**
         * @brief operator = Copy-Assigment Operator is not allowed
         * @param aRhs  Right side of Copy-Assigment Operator
         * @return
         */
        InitDiagramsController& operator= (const InitDiagramsController& aRhs);

    private:

        /**
         * @brief updateGuiWithCurrentData Update model and diagrams on view
         */
        void updateGuiWithCurrentData();

        /**
         * @brief m_inactiveModel SensorModel to store inactive sensor data from database
         */
        SensorModel& m_inactiveModel;

        /**
         * @brief m_activeModel SensorModel to store actvie sensor data from database
         */
        SensorModel& m_activeModel;
};

#endif // INITDIAGRAMSCONTROLLER_H
