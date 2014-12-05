QT += qml quick

# needed because of QCustom Plot
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += main.cpp \
    Model/sensordata.cpp \
    Model/devicedata.cpp \
    Model/devicemodel.cpp \
    Controler/connectionbuttoncontroler.cpp \
    Controler/searchdevicebuttoncontroler.cpp \
    Model/sensormodel.cpp \
    Controler/printbuttoncontroller.cpp \
    customplotitem.cpp \
    ../../third_party/qcustomplot.cpp \
    Controler/updatebuttoncontroler.cpp

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += qml.qrc \

HEADERS += \
    Model/sensordata.h \
    Model/devicedata.h \
    Model/devicemodel.h \
    Controler/connectionbuttoncontroler.h \
    Controler/searchdevicebuttoncontroler.h \
    RessourceFilePaths.h \
    Model/sensormodel.h \
    Controler/printbuttoncontroller.h \
    customplotitem.h \
    ../../third_party/qcustomplot.h \
    Controler/updatebuttoncontroler.h

DESTPATH = .
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH/View

INSTALLS += target qml
