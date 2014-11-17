TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \

TRANSLATIONS = Language_Files/app_de_DE.ts \

RESOURCES += \
    qml.qrc

# Default rules for deployment.
include(deployment.pri)
