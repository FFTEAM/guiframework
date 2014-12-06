#ifndef PRINTBUTTONCONTROLLER_H
#define PRINTBUTTONCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <Model/sensormodel.h>
#include <QTextDocument>

class PrintButtonController : public QObject
{
    Q_OBJECT
    public:

        explicit PrintButtonController(QObject* aParent = 0);

    signals:

    public slots:

        void clickPrintButtonSlot();

    private:

        void createSensorDataFile(QPrinter& aPrinter, SensorDataType aType,const QString aOverviewName);
};

#endif // PRINTBUTTONCONTROLLER_H
