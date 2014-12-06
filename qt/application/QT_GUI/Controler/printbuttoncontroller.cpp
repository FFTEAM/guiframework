#include "printbuttoncontroller.h"

PrintButtonController::PrintButtonController(QObject* aParent) :QObject(aParent)
{
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("printActionName");
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
    qDebug() << "print slot called";
    QPrinter printer;
    QPrintDialog printDialog(&printer);
    if (printDialog.exec() == QDialog::Accepted)
    {
        createSensorDataFile(printer, ACTIVE_SENSOR_DATA, "Overview Active Data");
        printer.newPage();
        createSensorDataFile(printer, INACTIVE_SENSOR_DATA, "Overview Inactive Data");
    }
}

void PrintButtonController::createSensorDataFile(QPrinter &aPrinter, SensorDataType aType,const QString aOverviewName)
{
    QString htmlBegin = "<html>";
    QString htmlEnd = "</html>";
    QString htmlBodyBegin = "<body>";
    QString htmlBodyEnd = "</body>";
    QString htmlHeadLine = "<h1>" +  aOverviewName + "</h1>";
    QString htmlTableCaptionRow = "<tr><th>Date</th><th>HeartRate</th></tr>";
    QString htmlTableRow;

    SensorModel* model = &SensorModel::getInstance(aType);
    for(int index = 0; index< model->getSensorModelCount(); index++)
    {
        const SensorData* data = model->getSingleSensorData(index);
        htmlTableRow += "<tr><td align=\"center\" valign=\"middle\">" + data->getDate() + "</td><td align=\"center\" valign=\"middle\">" + data->getHeartRate() + "</td></tr>";
    }

    QString htmlTable = "<br><br>";
    htmlTable += "<table align=\"center\" border = \"2\">" + htmlTableCaptionRow + htmlTableRow + "</table>";

    QString htmlText =  htmlBegin + htmlBodyBegin + htmlHeadLine + htmlTable + htmlBodyEnd + htmlEnd;

    //qDebug() << htmlText;

    QTextDocument doc;
    doc.setHtml(htmlText);
    doc.print(&aPrinter);
}
