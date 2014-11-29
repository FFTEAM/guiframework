#ifndef CONNECTIONBUTTONCONTROLER_H
#define CONNECTIONBUTTONCONTROLER_H

#include <QDebug>
#include <QObject>
#include "Model/devicedata.h"
#include "Model/devicemodel.h"
#include "RessourceFilePaths.h"

class ConnectionButtonControler : public QObject
{
    Q_OBJECT
    public:

        explicit ConnectionButtonControler(QObject *aParent = 0, DeviceModel* aModel = 0);

        signals:

        public slots:

            void clickConnectionButtonSlot(const int aCurrentIndex);

        private:

            DeviceModel* m_dataList;

};

#endif // CONNECTIONBUTTONCONTROLER_H
