#ifndef IMPORTBUTTONCONTROLER_H
#define IMPORTBUTTONCONTROLER_H

#include <QDebug>
#include <QObject>
#include "Model/sensormodel.h"
#include "RessourceFilePaths.h"

class ImportButtonControler : public QObject
{
    Q_OBJECT
    public:
        explicit ImportButtonControler(QObject* aParent = 0, SensorModel* aModel = 0);

    signals:

    public slots:

            void clickImportButtonSlot();

    private:

            SensorModel* m_SensorList;

};

#endif // IMPORTBUTTONCONTROLER_H
