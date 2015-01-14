//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   printcontroller.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   20.12.2014 14:56:00 GMT
  *
  * @brief  Implementation file of PrintController class
  *
  */

#include "printcontroller.h"
#include <QErrorMessage>

PrintController::PrintController(QObject* aParent,
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

void PrintController::clickPrintButtonSlot()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer);

    /*  Exception handling is in this case needed, because on windows system qPrintDialog
        has several unresolved bugs */
    try
    {
        // Show print dialog on view
        if (printDialog.exec() == QDialog::Accepted)
        {
            QObject* currentTab = parent()->findChild<QObject*>("TabViewName");
            if(currentTab)
            {
                switch(currentTab->property("currentIndex").toInt())
                {
                    case 0: createSensorDataFile(printer, m_inactiveDatamodel, tr("Overview Inactive Data"));break;

                    case 1: createSensorDataFile(printer, m_activeDataModel, tr("Overview Active Data"));break;

                    default: qDebug() << "No valid tab selected";
                }
            }
            else qDebug() << "No child found";
        }
    }
    catch(std::exception& e)
    {
        qDebug() << "print function fail";
        qDebug() << e.what();

        // create and show error message to inform user that print function not work on this system
        QErrorMessage errorMessage;
        errorMessage.showMessage(tr("Error in print function"));
    }
}

void PrintController::createSensorDataFile(QPrinter& aPrinter, const SensorModel& aModel, const QString aOverviewName)
{
    // create html string to format print output
    QString htmlBegin = "<html>";
    QString htmlEnd = "</html>";
    QString htmlBodyBegin = "<body>";
    QString htmlBodyEnd = "</body>";
    QString htmlHeadLine = "<h1 align=\"center\">" + aOverviewName + "</h1>";
    QString htmlTableCaptionRow = "<tr><th>Date</th><th>HeartRate</th></tr>";
    QString htmlTableRow;

    // get all information form model and add to print output
    for(int index = 0; index < aModel.getSensorModelCount(); index++)
    {
        const SensorData* data = aModel.getSingleSensorData(index);
        QString heartRate;
        heartRate.append(QString("%1").arg(data->getHeartRate()));
        QString date = data->getDate().toString("dd.MM.yyyy hh:mm:ss");
        htmlTableRow = htmlTableRow.append("<tr><td align=\"center\" valign=\"middle\">").append(date);
        htmlTableRow = htmlTableRow.append("</td><td align=\"center\" valign=\"middle\">").append(heartRate).append("</td></tr>");
    }

    QString htmlTable = "<br><br>";
    htmlTable = htmlTable.append("<table align=\"center\" border = \"1\">").append(htmlTableCaptionRow).append(htmlTableRow).append("</table>");

    QString htmlText =  htmlBegin.append(htmlBodyBegin).append(htmlHeadLine).append(htmlTable).append(htmlBodyEnd).append(htmlEnd);

    QTextDocument doc;
    doc.setHtml(htmlText);
    doc.print(&aPrinter);
}
