//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   main.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 13:01:00 GMT
  *
  * @brief  In der Main.cpp wird die Application erzeugt und die Sprache festgelegt. Zusätzlich
  * werden die Controller und die Größe des Applikationsfenster initialisert. Abschließend werden die
  * Diagramm zur darstellung der Messadten an der View registriert.
  *
  */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>

#include "Model/Data/sensordata.h"
#include "Model/sensormodel.h"
#include "Model/activesensorcalcmodel.h"
#include "Model/activesensormodel.h"
#include "Model/inactivesensorcalcmodel.h"
#include "Model/inactivesensormodel.h"
#include "Controler/printbuttoncontroller.h"
#include "Controler/updatebuttoncontroller.h"
#include "RessourceFilePaths.h"
#include "Diagram/customplotbarchart.h"
#include "Diagram/customplotlinechart.h"
#include "Connection/BroadcastReceiver.h"
#include "Connection/TcpServer.h"
#include "Settings/Settings.h"

/**
 * @brief main  Main-Methode erzeugt Applikation und offenet die View
 * @param argc  Anzahl der Elemente von argv
 * @param argv  Enthält die Kommandozeilen Parameter
 * @return 0 falls alles OK ist
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("GUI-Frameworks");
    QCoreApplication::setApplicationName("HeartRate");

    Settings& test = Settings::getInstance();
    if (!test)
    {
        qDebug("FATAL error while instanciating Settings!!");
        return 1;
    }

    QApplication app(argc, argv);

    BroadcastReceiver bcReceiver;
    // run broadcast receiver thread loop:
    bcReceiver.start();

    TcpServer server;
    // listen for incoming data connections:
    server.startServer();

    // create sensorInactiveData Model
    InactiveSensorModel* inactiveSensorModel = &InactiveSensorModel::getInstance();

    // create sensorActiveModel
    ActiveSensorModel* activeSensorModel = &ActiveSensorModel::getInstance();

    // create inactiveCalcSensorModel
    InactiveSensorCalcModel* inactiveCalcSensorModel = &InactiveSensorCalcModel::getInstance();

    // create activeCalcSensorModel
    ActiveSensorCalcModel* activeCalcSensorModel = &ActiveSensorCalcModel::getInstance();

    qmlRegisterType<CustomPlotBarChart>("CostumPlot", 1, 0, "CustomPlotBarChart");
    qmlRegisterType<CustomPlotLineChart>("CostumPlot", 1, 0, "CustomPlotLineChart");

    //multiple language
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/Language_Files/app_" + QLocale::system().name() + ".qm");
    app.installTranslator(&myappTranslator);

    QQmlApplicationEngine engine;

    QQmlContext* contex = engine.rootContext();
    if(contex)
    {
        // set Model to view
        contex->setContextProperty("inactiveSensorDataModel", inactiveSensorModel);
        contex->setContextProperty("activeSensorDataModel", activeSensorModel);
        contex->setContextProperty("inactiveSensorCalcModel", inactiveCalcSensorModel);
        contex->setContextProperty("activeSensorCalcModel", activeCalcSensorModel);
    }
    else qDebug() << "Error no contex is set";

    // load qml file to engine
    engine.load(QUrl(MAIN_VIEW));

    QObject* root = engine.rootObjects().at(0);
    if(root)
    {
        // initate tabs
        QObject* tabView = root->findChild<QObject*>("TabViewName");
        if(tabView)
        {
            const int countTabs = tabView->property("count").toInt();
            for(int i = countTabs-1 ; i >= 0; i--)
            {
                tabView->setProperty("currentIndex",i);
            }
        }
        else qDebug() << "No tabview object found";
    }
    else qDebug() << "No root object available";

    // set controler
    PrintButtonController printController(root);
    UpdateButtonController updateController(root);

    int ret = app.exec();
    bcReceiver.exit();
    return ret;
}
