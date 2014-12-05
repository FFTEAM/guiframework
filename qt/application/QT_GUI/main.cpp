#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>

#include "Model/sensordata.h"
#include "Model/sensormodel.h"
#include "Controler/printbuttoncontroller.h"
#include "Controler/updatebuttoncontroler.h"
#include "RessourceFilePaths.h"
#include "CustomPlotItem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // create sensorData Model
    SensorModel* modelSensorData = &SensorModel::getInstance();
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","200","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","202","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","10","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","40","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","200","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","202","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","10","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","40","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","70","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","100","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","200","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","202","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","10","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","40","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData->addSensorData(SensorData("31-12-2009 23:00:01","120","2"));

    qmlRegisterType<CustomPlotItem>("CostumPlot", 1, 0, "CustomPlotItem");

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
        contex->setContextProperty("sensorDataModel", modelSensorData);
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
    PrintButtonController controller(root, modelSensorData);
    UpdateButtonControler controller2 (root, modelSensorData);

    return app.exec();
}
