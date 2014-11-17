#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //multiple language
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/Language_Files/app_" + QLocale::system().name() + ".qm");
    app.installTranslator(&myappTranslator);

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:/View/main.qml")));
    view.show();

    return app.exec();
}
