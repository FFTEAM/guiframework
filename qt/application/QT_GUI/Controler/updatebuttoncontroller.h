#ifndef UPDATEBUTTONCONTROLLER_H
#define UPDATEBUTTONCONTROLLER_H

#include <QDebug>
#include <QObject>
#include "Model/sensordata.h"
#include "Model/sensormodel.h"

class UpdateButtonController : public QObject
{
    Q_OBJECT
    public:

        explicit UpdateButtonController(QObject* aParent = 0);

    signals:

    public slots:

        void updateActionSlot();

    private:

        UpdateButtonController(const UpdateButtonController& aOther);
        UpdateButtonController& operator= (const UpdateButtonController& aRhs);
};

#endif // UPDATEBUTTONCONTROLLER_H
