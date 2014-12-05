#ifndef PRINTBUTTONCONTROLLER_H
#define PRINTBUTTONCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <Model/sensormodel.h>

class PrintButtonController : public QObject
{
    Q_OBJECT
    public:

        explicit PrintButtonController(QObject* aParent = 0, SensorModel* aModel = 0);

    signals:

    public slots:

        void clickPrintButtonSlot();

    private:

        SensorModel* m_SensorList;

};

#endif // PRINTBUTTONCONTROLLER_H
