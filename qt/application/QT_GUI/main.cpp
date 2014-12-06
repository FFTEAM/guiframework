#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>

#include "Model/sensordata.h"
#include "Model/sensormodel.h"
#include "Controler/printbuttoncontroller.h"
#include "Controler/updatebuttoncontroler.h"
#include "RessourceFilePaths.h"
#include "customplotbarchart.h"
#include "customplotlinechart.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // create sensorInactiveData Model
    SensorModel* inactiveSensorDataModel = &SensorModel::getInstance(INACTIVE_SENSOR_DATA);
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","200","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","202","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","10","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","40","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    inactiveSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));

    // create sensorActiveModel
    SensorModel* activeSensorDataModel = &SensorModel::getInstance(ACTIVE_SENSOR_DATA);
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","10","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","20","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","30","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","40","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","50","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","60","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","80","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","90","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","110","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","130","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","140","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","130","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","121","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","122","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","123","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","125","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","124","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","123","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","122","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","140","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","200","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","190","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","150","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    activeSensorDataModel->addSensorData(SensorData("31-12-2009 23:00:01","50","2"));

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

        QQuickWindow *window = qobject_cast<QQuickWindow*>(root);
        if (window)
        {
            window->setMaximumHeight(600);
            window->setMinimumHeight(600);
            window->setMaximumWidth(900);
            window->setMinimumWidth(900);
            window->show();
        }
        else qFatal("Error: No window found!");
    }
    else qDebug() << "No root object available";

    // set controler
    PrintButtonController printController(root);
    UpdateButtonControler updateController(root);

    return app.exec();
}
