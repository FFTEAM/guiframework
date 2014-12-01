#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QTranslator>
#include <QDebug>

#include "Model/sensordata.h"
#include "Model/devicedata.h"
#include "Model/devicemodel.h"
#include "Controler/importbuttoncontroler.h"
#include "Controler/connectionbuttoncontroler.h"
#include "Controler/searchdevicebuttoncontroler.h"
#include "Controler/printbuttoncontroller.h"
#include "RessourceFilePaths.h"
#include "Model/sensormodel.h"
#include "CustomPlotItem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CustomPlotItem>("CostumPlot", 1, 0, "CustomPlotItem");

    //multiple language
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/Language_Files/app_" + QLocale::system().name() + ".qm");
    app.installTranslator(&myappTranslator);

    // create device Model
    DeviceModel model;
    model.addDevice(DeviceData("Device 1"));
    model.addDevice(DeviceData("Device 2"));
    model.addDevice(DeviceData("Device 3"));

    // create sensorData Model
    SensorModel modelSensorData;
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));
    modelSensorData.addSensorData(SensorData("31-12-2009 23:00:01","89","2"));

    // create view
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();

    // set Model to view
    ctxt->setContextProperty("deviceModel", &model);
    ctxt->setContextProperty("sensorDataModel", &modelSensorData);

    // add qml File to View
    view.setSource(QUrl(MAIN_VIEW));

    // initate tabs
    QObject* tabView = view.rootObject()->findChild<QObject*>("TabViewName");
    const int countTabs = tabView->property("count").toInt();
    for(int i = countTabs-1 ; i >= 0; i--)
    {
        tabView->setProperty("currentIndex",i);
    }

    // set controler
    ImportButtonControler controller(view.rootObject(), &modelSensorData);
    ConnectionButtonControler controller1(view.rootObject(), &model);
    SearchDeviceButtonControler controller2 (view.rootObject(), &model);
    PrintButtonController controller3(view.rootObject(), &modelSensorData);

    view.setMinimumHeight(500);
    view.setMinimumWidth(700);
    view.setMaximumHeight(500);
    view.setMaximumWidth(700);
    view.show();

    return app.exec();
}
