QT += qml quick sql

# needed because of QCustom Plot
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

SOURCES +=  main.cpp \
            Thirdparty/qcustomplot.cpp \
            Model/Data/sensordata.cpp \
            Model/sensormodel.cpp \
            Controler/printbuttoncontroller.cpp \
            Diagram/customplotbarchart.cpp \
            Diagram/customplotlinechart.cpp \
            Controler/updatebuttoncontroller.cpp \
            Connection/DataReceiver.cpp \
            Connection/BroadcastReceiver.cpp \
            Connection/TcpConnection.cpp \
            Connection/TcpServer.cpp \
    Model/Data/calcsensordata.cpp \
    Model/activesensorcalcmodel.cpp \
    Model/activesensormodel.cpp \
    Model/inactivesensorcalcmodel.cpp \
    Model/inactivesensormodel.cpp \
    Model/sensorcalcmodel.cpp \
    ImportExport/ImportExport.cpp \
    Settings/Settings.cpp

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += qml.qrc \

HEADERS += \
            Model/Data/sensordata.h \
            Thirdparty/qcustomplot.h \
            RessourceFilePaths.h \
            Model/sensormodel.h \
            Controler/printbuttoncontroller.h \
            Diagram/customplotbarchart.h \
            Diagram/customplotlinechart.h \
            Controler/updatebuttoncontroller.h \
            Connection/DataReceiver.h \
            Connection/BroadcastReceiver.h \
            Connection/TcpConnection.h \
            Connection/TcpServer.h \
    Model/Data/calcsensordata.h \
    Model/sensorcalcmodel.h \
    Model/inactivesensorcalcmodel.h \
    Model/activesensorcalcmodel.h \
    Model/inactivesensormodel.h \
    Model/activesensormodel.h \
    ImportExport/ImportExport.h \
    Settings/Settings.h

DESTPATH = .
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH/View

INSTALLS += target qml
