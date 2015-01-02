//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   main.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   17.11.2014 15:05:00 GMT
  *
  * @brief  Implementation file of main.cpp
  *
  * In this file all language files are load. QML engine is definded and view is showed.
  * All models and controllers are init. Data Receiver and database get installed.
  *
  */

#include <QApplication>
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
#include "Controller/printcontroller.h"
#include "Controller/selectioncontroller.h"
#include "Controller/initdiagramscontroller.h"
#include "Controller/filtercontroller.h"
#include "Controller/tableselectioncontroller.h"

// inlcude path for diagrams on view
#include "Diagram/customplotbarchart.h"
#include "Diagram/customplotlinechart.h"

#include "RessourceFilePaths.h"
#include "Connection/BroadcastReceiver.h"
#include "Connection/TcpServer.h"
#include "Settings/Settings.h"
#include "ImportExport/ImportExport.h"

/** declare a new QVariant typ for view */
Q_DECLARE_METATYPE(SensorModel)

/**
 * @brief main  main method to create application
 * @param argc  count of elements in argv
 * @param argv  include all commando line parameter
 * @return Return 0 if ok otherwise a error code not equal 0
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("GUI-Frameworks");
    QCoreApplication::setApplicationName("HeartRate");

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/Images/heart_icon.png"));

    //multiple language
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/Language_Files/app_" + QLocale::system().name() + ".qm");
    app.installTranslator(&myappTranslator);

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

    BroadcastReceiver bcReceiver;
    // run broadcast receiver thread loop:
    bcReceiver.start();

    TcpServer server;
    // listen for incoming data connections:
    server.startServer();

    // create sensorInactiveData Model
    SensorModel inactiveSensorModel;

    // create inactiveCalcSensorModel
    InactiveSensorCalcModel inactiveCalcSensorModel(inactiveSensorModel);

    // create sensorActiveModel
    SensorModel activeSensorModel;

    // create sensorActiveTable Model
    SensorModel activeSensorTableModel;

    // create activeCalcSensorModel
    ActiveSensorCalcModel activeCalcSensorModel(activeSensorModel);

    // create selectionValue models
    SelectionModel activeYearModel, activeMonthModel;

    qmlRegisterType<CustomPlotBarChart>("CostumPlot", 1, 0, "CustomPlotBarChart");
    qmlRegisterType<CustomPlotLineChart>("CostumPlot", 1, 0, "CustomPlotLineChart");

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
        contex->setContextProperty("activeSensorTableModel", &activeSensorTableModel);
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
    FilterController filterController(root, inactiveSensorModel, inactiveCalcSensorModel, dataStorage);
    SelectionController selectionController(root, activeYearModel, activeMonthModel, activeSensorModel,activeSensorTableModel, activeCalcSensorModel, dataStorage);
    TableSelectionController tableController(root, activeSensorTableModel, activeSensorModel, activeCalcSensorModel, dataStorage);
    PrintController printController(root, inactiveSensorModel, activeSensorModel);
    InitDiagramsController initController(root, inactiveSensorModel, activeSensorModel);

    int ret = app.exec();
    bcReceiver.exit();
    return ret;
}
