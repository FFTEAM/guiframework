#ifndef SENSORCALCMODEL_H
#define SENSORCALCMODEL_H

#include <QAbstractListModel>
#include "Model/Data/calcsensordata.h"
#include "Model/sensormodel.h"
#include <QDebug>

class SensorCalcModel: public QAbstractListModel
{
    Q_OBJECT
    public:

        explicit SensorCalcModel(QObject* aParent = 0);

        void setNewSensorCalcModel(const QList<CalcSensorData>& aSensorModel);

        /**
         * @brief updateCalcValues aktualisiert die Attribute, wenn sich die Daten ändern
         */
        void updateCalcValues(const SensorModel& aModel);

    protected:

        /**
         * @brief m_calcSensorList Liste mit den berechneten Werten
         */
        QList<CalcSensorData> m_calcSensorList;
};

#endif // SENSORCALCMODEL_H
