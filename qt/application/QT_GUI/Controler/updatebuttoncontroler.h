#ifndef UPDATEBUTTONCONTROLER_H
#define UPDATEBUTTONCONTROLER_H

#include <QDebug>
#include <QObject>
#include "Model/sensordata.h"
#include "Model/sensormodel.h"

class UpdateButtonControler : public QObject
{
    Q_OBJECT
    public:
        explicit UpdateButtonControler(QObject* aParent = 0);

    signals:

    public slots:

            void updateActionSlot();
};

#endif // UPDATEBUTTONCONTROLER_H
