QT += qml quick

# needed because of QCustom Plot
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES +=  main.cpp \
            Thirdparty/qcustomplot.cpp \
            Model/sensordata.cpp \
            Model/sensormodel.cpp \
            Controler/printbuttoncontroller.cpp \
            Diagram/customplotbarchart.cpp \
            Diagram/customplotlinechart.cpp \
            Controler/updatebuttoncontroller.cpp \
            Connection/DataReceiver.cpp \
            Connection/BroadcastReceiver.cpp \
            Connection/TcpConnection.cpp \
            Connection/TcpServer.cpp

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += qml.qrc \

HEADERS += \
            Model/sensordata.h \
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
            Connection/TcpServer.h

DESTPATH = .
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH/View

INSTALLS += target qml
