QT += qml quick sql

# needed because of QCustom Plot
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

SOURCES +=  main.cpp \
            Thirdparty/qcustomplot.cpp \
            Model/Data/sensordata.cpp \
            Model/sensormodel.cpp \
            Controller/printbuttoncontroller.cpp \
            Diagram/customplotbarchart.cpp \
            Diagram/customplotlinechart.cpp \
            Controller/updatebuttoncontroller.cpp \
            Connection/DataReceiver.cpp \
            Connection/BroadcastReceiver.cpp \
            Connection/TcpConnection.cpp \
            Connection/TcpServer.cpp \
            Model/Data/calcsensordata.cpp \
            Model/activesensorcalcmodel.cpp \
            Model/inactivesensorcalcmodel.cpp \
            Model/sensorcalcmodel.cpp \
            ImportExport/ImportExport.cpp \
            Settings/Settings.cpp \
            Model/selectionmodel.cpp

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += qml.qrc \

HEADERS += \
            Model/Data/sensordata.h \
            Thirdparty/qcustomplot.h \
            RessourceFilePaths.h \
            Model/sensormodel.h \
            Controller/printbuttoncontroller.h \
            Diagram/customplotbarchart.h \
            Diagram/customplotlinechart.h \
            Controller/updatebuttoncontroller.h \
            Connection/DataReceiver.h \
            Connection/BroadcastReceiver.h \
            Connection/TcpConnection.h \
            Connection/TcpServer.h \
            Model/Data/calcsensordata.h \
            Model/sensorcalcmodel.h \
            Model/inactivesensorcalcmodel.h \
            Model/activesensorcalcmodel.h \
            ImportExport/ImportExport.h \
            Settings/Settings.h \
            Model/selectionmodel.h

DESTPATH = .
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH/View

INSTALLS += target qml
