//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   printbuttoncontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  Diese Header-Datei enthält alle Deklarationen der Klasse PrintButtonControllers
  *
  */

#ifndef PRINTBUTTONCONTROLLER_H
#define PRINTBUTTONCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include "Model/activesensormodel.h"
#include "Model/inactivesensormodel.h"
#include "Model/sensormodel.h"
#include <QTextDocument>

/**
 * @brief The PrintButtonController class
 */
class PrintButtonController : public QObject
{
    Q_OBJECT
    public:

        /** PrintButtonController ist der Konstruktor der Klasse PrintButtonController
         * @param aParent Zeiger auf die Basisklasse QObject
         *
         * Der Konstruktor verbindet das Signal von dem GUI mit dem entsprechenden SLOT
         */
        explicit PrintButtonController(QObject* aParent = 0);

    signals:

    public slots:

        /**
         * @brief clickPrintButtonSlot ist der Slot für das "printActionIsTriggered" Signal
         */
        void clickPrintButtonSlot();

    private:

        /**
         * @brief PrintButtonController Nicht in Verwendung (Definition fehlt)
         * @param aOther Referenz auf ein Objekt der Klasse PrintButtonController
         */
        PrintButtonController(const PrintButtonController& aOther);

        /**
         * @brief operator = Nicht in Verwendung (Definition fehlt)
         * @param aRhs Referenz auf ein Objekt der Klasse PrintButtonController
         * @return Liefert ein Objekt der Klasse PrintButtonController zurück (Konkatination möglich)
         */
        PrintButtonController& operator= (const PrintButtonController& aRhs);

        /**
         * @brief createSensorDataFile erzeugt ein QTextDocument für die spätere Druckfunktion.
         * @param aPrinter ist eine Instanz der Klasse QPrinter
         * @param aType legt fest, ob die Pulswerte der Ruhephase oder der Belastungsphase verwendet werden sollen
         * @param aOverviewName legt die Überschrift für den Ausdruck fest
         *
         * Diese Methode erzeugt auf Grundlage der Parameter ein QTextDocument. Dieses Dokument wird anhand von HTML Code beschrieben.
         * Der Vorteil hierfür sind die vielen formatierungsmöglichkeiten von HTML. Abschließend wird das Dokument dem QPrinter übergeben.
         */
        void createSensorDataFile(QPrinter& aPrinter,const SensorModel& aModel, const QString aOverviewName);
};

#endif // PRINTBUTTONCONTROLLER_H
