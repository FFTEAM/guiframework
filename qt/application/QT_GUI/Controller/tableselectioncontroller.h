#ifndef TABLESELECTIONCONTROLLER_H
#define TABLESELECTIONCONTROLLER_H

#include <QObject>
#include "Model/sensormodel.h"
#include "Model/activesensorcalcmodel.h"
#include "ImportExport/ImportExport.h"

class TableSelectionController : public QObject
{
    Q_OBJECT
    public:

        TableSelectionController(QObject* aParent,
                                 SensorModel& aRunModel,
                                 SensorModel& aActiveSensorModel,
                                 ActiveSensorCalcModel& aActiveSensorCalcModel,
                                 ImportExport& aStorage);

    public slots:

        void selectSingleRunSlot(int aIndex);

    private:

        SensorModel& m_runModel;

        SensorModel& m_activeSensorModel;

        ActiveSensorCalcModel& m_activeSensorCalcModel;

        ImportExport& m_importExportStorage;

        void updateGuiWithCurrentData();
};

#endif // TABLESELECTIONCONTROLLER_H
