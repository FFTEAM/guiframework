//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   main.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
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

// include paths for data objects
#include "Model/Data/sensordata.h"

// include path for models
#include "Model/sensormodel.h"
#include "Model/activesensorcalcmodel.h"
#include "Model/inactivesensorcalcmodel.h"
#include "Model/selectionmodel.h"

// include paths for contollers
#include "Controller/printbuttoncontroller.h"
#include "Controller/selectioncontroller.h"
#include "Controller/initdiagramscontroller.h"
#include "Controller/filtercontroller.h"

// inlcude path for diagrams on view
#include "Diagram/customplotbarchart.h"
#include "Diagram/customplotlinechart.h"

#include "RessourceFilePaths.h"
#include "Connection/BroadcastReceiver.h"
#include "Connection/TcpServer.h"
#include "Settings/Settings.h"
#include "ImportExport/ImportExport.h"

Q_DECLARE_METATYPE(SensorModel)

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
    /******************************************
    * instanciate dataStorage
    * has to be referenced to the model
    * which need the data
    *******************************************/
    ImportExport dataStorage;
    if (!dataStorage)
    {
        qDebug("FATAL error while creating Database instance");
        return 1;
    }

    QApplication app(argc, argv);

    BroadcastReceiver bcReceiver;
    // run broadcast receiver thread loop:
    bcReceiver.start();

    TcpServer server;
    // listen for incoming data connections:
    server.startServer();

    // EXAMPLE DATA:
    QList<const SensorData*> sensorDataI;
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 1)), 200, 5));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 2)), 100, 3));
    sensorDataI.append(new SensorData(QDateTime(QDate(2015, 1, 1), QTime(0, 0, 3)), 50, 3));

    QList<const SensorData*> sensorDataA;
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 1)), 230, 5));
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 2)), 120, 10));
    sensorDataA.append(new SensorData(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 3)), 30, 3));

    QList<QString> selectionYearData;
    selectionYearData.append("2010");
    selectionYearData.append("2011");
    selectionYearData.append("2012");
    selectionYearData.append("2013");
    selectionYearData.append("2014");
    selectionYearData.append("2015");

    // create sensorInactiveData Model
    SensorModel inactiveSensorModel;
    inactiveSensorModel.setNewSensorModel(sensorDataI);

    // create sensorActiveModel
    SensorModel activeSensorModel;
    activeSensorModel.setNewSensorModel(sensorDataA);

    // create inactiveCalcSensorModel
    InactiveSensorCalcModel inactiveCalcSensorModel(inactiveSensorModel);

    // create activeCalcSensorModel
    ActiveSensorCalcModel activeCalcSensorModel(activeSensorModel);

    // create selectionValue models
    SelectionModel activeYearModel, activeMonthModel, activeWeekModel;
    activeYearModel.setNewSelectionModel(selectionYearData);

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
        contex->setContextProperty("inactiveSensorDataModel", &inactiveSensorModel);
        contex->setContextProperty("activeSensorDataModel", &activeSensorModel);
        contex->setContextProperty("inactiveSensorCalcModel", &inactiveCalcSensorModel);
        contex->setContextProperty("activeSensorCalcModel", &activeCalcSensorModel);
        contex->setContextProperty("activeSelectionYearModel", &activeYearModel);
        contex->setContextProperty("activeSelectionMonthModel", &activeMonthModel);
        contex->setContextProperty("activeSelectionWeekModel", &activeWeekModel);
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
    PrintButtonController printController(root, inactiveSensorModel, activeSensorModel);
    InitDiagramsController initController(root, inactiveSensorModel, activeSensorModel);
    SelectionController selectionController(root, activeYearModel, activeMonthModel, activeWeekModel, activeSensorModel);
    FilterController filterController(root, inactiveSensorModel, inactiveCalcSensorModel);

    int ret = app.exec();
    bcReceiver.exit();
    return ret;
}
