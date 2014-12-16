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
#include "Controler/printbuttoncontroller.h"
#include "Controler/updatebuttoncontroller.h"
#include "RessourceFilePaths.h"
#include "Diagram/customplotbarchart.h"
#include "Diagram/customplotlinechart.h"
#include "Connection/BroadcastReceiver.h"
#include "Connection/TcpServer.h"

/**
 * @brief main  Main-Methode erzeugt Applikation und offenet die View
 * @param argc  Anzahl der Elemente von argv
 * @param argv  Enthält die Kommandozeilen Parameter
 * @return 0 falls alles OK ist
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BroadcastReceiver bcReceiver;
    // run broadcast receiver thread loop:
    bcReceiver.start();

    TcpServer server;
    // listen for incoming data connections:
    server.startServer();

    // create sensorInactiveData Model
    SensorModel* inactiveSensorDataModel = &SensorModel::getInstance(INACTIVE_SENSOR_DATA);
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","89","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","120","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","70","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","100","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","200","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","202","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","10","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","40","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","89","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","120","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","70","2"));
    inactiveSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","100","2"));

    // create sensorActiveModel
    SensorModel* activeSensorDataModel = &SensorModel::getInstance(ACTIVE_SENSOR_DATA);
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","10","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","20","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","30","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","40","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","50","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","60","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","70","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","80","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","90","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","100","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","110","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","120","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","130","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","140","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","130","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","120","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","121","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","122","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","123","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","125","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","124","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","123","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","122","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","140","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","200","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","190","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","150","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","100","2"));
    activeSensorDataModel->addSensorData(new SensorData("31-12-2009 23:00:01","50","2"));

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
        contex->setContextProperty("inactiveSensorDataModel", inactiveSensorDataModel);
        contex->setContextProperty("activeSensorDataModel", activeSensorDataModel);
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

        // THIS IS DONE IN QML NOW:
#if 0
        QQuickWindow *window = qobject_cast<QQuickWindow*>(root);
        if (window)
        {
            QDesktopWidget widget;
            QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
            qDebug() << "Current Height : " << mainScreenSize.height();
            qDebug() << "Current Width  : " << mainScreenSize.width();

            if(mainScreenSize.height() < 600 || mainScreenSize.width() < 900)
            {
                qFatal("Window size too small");
            }
            else
            {
                window->setMaximumHeight(600);
                window->setMinimumHeight(600);
                window->setMaximumWidth(900);
                window->setMinimumWidth(900);
                window->show();
            }
        }
        else qFatal("Error: No window found!");
#endif
    }
    else qDebug() << "No root object available";

    // set controler
    PrintButtonController printController(root);
    UpdateButtonController updateController(root);

    int ret = app.exec();
    bcReceiver.exit();
    return ret;
}
