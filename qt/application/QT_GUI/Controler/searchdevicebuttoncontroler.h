#ifndef SEARCHDEVICEBUTTONCONTROLER_H
#define SEARCHDEVICEBUTTONCONTROLER_H

#include <QDebug>
#include <QObject>
#include "Model/devicedata.h"
#include "Model/devicemodel.h"
#include "RessourceFilePaths.h"

class SearchDeviceButtonControler : public QObject
{
    Q_OBJECT
    public:

        explicit SearchDeviceButtonControler(QObject* aParent = 0, DeviceModel* aModel = 0);

    signals:

    public slots:

        void clickSearchDeviceButtonSlot();

    private:

        DeviceModel* m_dataList;

};

#endif // SEARCHDEVICEBUTTONCONTROLER_H
