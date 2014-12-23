//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   printbuttoncontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "printbuttoncontroller.h"

PrintButtonController::PrintButtonController(QObject* aParent,
                                             SensorModel& aModelForInactiveData,
                                             SensorModel& aModelForActiveData) :    QObject(aParent),
                                                                                    m_inactiveDatamodel(aModelForInactiveData),
                                                                                    m_activeDataModel(aModelForActiveData)
{
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("printActionName");
        if(child)
        {
            QObject::connect(child, SIGNAL(printActionIsTriggered()), this, SLOT(clickPrintButtonSlot()));
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
        createSensorDataFile(printer, m_activeDataModel, "Overview Active Data");
        printer.newPage();
        createSensorDataFile(printer, m_inactiveDatamodel, "Overview Inactive Data");
    }
}

void PrintButtonController::createSensorDataFile(QPrinter& aPrinter, const SensorModel& aModel, const QString aOverviewName)
{
    QString htmlBegin = "<html>";
    QString htmlEnd = "</html>";
    QString htmlBodyBegin = "<body>";
    QString htmlBodyEnd = "</body>";
    QString htmlHeadLine = "<h1 align=\"center\">" + aOverviewName + "</h1>";
    QString htmlTableCaptionRow = "<tr><th>Date</th><th>HeartRate</th></tr>";
    QString htmlTableRow;

    for(int index = 0; index< aModel.getSensorModelCount(); index++)
    {
        const SensorData* data = aModel.getSingleSensorData(index);
        htmlTableRow += "<tr><td align=\"center\" valign=\"middle\">" + data->getDate().toString("dd MM yy hh:mm:ss") + "</td><td align=\"center\" valign=\"middle\">" + data->getHeartRate() + "</td></tr>";
    }

    QString htmlTable = "<br><br>";
    htmlTable += "<table align=\"center\" border = \"2\">" + htmlTableCaptionRow + htmlTableRow + "</table>";

    QString htmlText =  htmlBegin + htmlBodyBegin + htmlHeadLine + htmlTable + htmlBodyEnd + htmlEnd;

    QTextDocument doc;
    doc.setHtml(htmlText);
    doc.print(&aPrinter);
}
