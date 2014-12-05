#ifndef UPDATEBUTTONCONTROLER_H
#define UPDATEBUTTONCONTROLER_H

#include <QDebug>
#include <QObject>
#include "Model/sensormodel.h"
#include "RessourceFilePaths.h"

class UpdateButtonControler : public QObject
{
    Q_OBJECT
    public:
        explicit UpdateButtonControler(QObject* aParent = 0, SensorModel* aModel = 0);

    signals:

    public slots:

            void updateActionSlot();

    private:

            SensorModel* m_SensorList;

};

#endif // UPDATEBUTTONCONTROLER_H
