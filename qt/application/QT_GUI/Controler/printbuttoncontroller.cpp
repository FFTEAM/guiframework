#include "printbuttoncontroller.h"

PrintButtonController::PrintButtonController(QObject* aParent, SensorModel* aModel) :QObject(aParent),
                                                                                     m_SensorList(aModel)
{
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("printButtonName");
        if(child)
        {
            QObject::connect(child, SIGNAL(printButtonIsPressed()), this, SLOT(clickPrintButtonSlot()));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void PrintButtonController::clickPrintButtonSlot()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer);
    if (printDialog.exec() == QDialog::Accepted)
    {
         qDebug() << "print";
    }
}
