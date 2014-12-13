QT += qml quick

# needed because of QCustom Plot
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES +=  main.cpp \
            Model/sensordata.cpp \
            Model/sensormodel.cpp \
            Controler/printbuttoncontroller.cpp \
            ../../third_party/qcustomplot.cpp \
            customplotbarchart.cpp \
            customplotlinechart.cpp \
            Controler/updatebuttoncontroller.cpp

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += qml.qrc \

HEADERS += \
            Model/sensordata.h \
            RessourceFilePaths.h \
            Model/sensormodel.h \
            Controler/printbuttoncontroller.h \
            ../../third_party/qcustomplot.h \
            customplotbarchart.h \
            customplotlinechart.h \
            Controler/updatebuttoncontroller.h

DESTPATH = .
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH/View

INSTALLS += target qml
