//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   updatebuttoncontroller.h
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 13:40:00 GMT
  *
  * @brief  Diese Header-Datei enhält alle Deklarationen der Klasse UpdateButtonControllers
  *
  */

#ifndef UPDATEBUTTONCONTROLLER_H
#define UPDATEBUTTONCONTROLLER_H

#include <QDebug>
#include <QObject>
#include "Model/sensordata.h"
#include "Model/sensormodel.h"

/**
 * @brief The UpdateButtonController class
 */
class UpdateButtonController : public QObject
{
    Q_OBJECT
    public:

        /** UpdateButtonController ist der Konstruktor der Klasse UpdateButtonController
         * @param aParent Zeiger auf die Basisklasse QObject
         *
         * Der Konstruktor verbindet das Signal von dem GUI mit dem entsprechenden SLOT
         */
        explicit UpdateButtonController(QObject* aParent = 0);

    signals:

    public slots:

        /**
         * @brief updateActionSlot ist der Slot für das "updateActionIsTriggered" Signal
         */
        void updateActionSlot();

    private:

        /**
         * @brief UpdateButtonController Nicht in Verwendung (Definition fehlt)
         * @param aOther Referenz auf ein Objekt der Klasse UpdateButtonController
         */
        UpdateButtonController(const UpdateButtonController& aOther);

        /**
         * @brief operator = Nicht in Verwendung (Definition fehlt)
         * @param aRhs Referenz auf ein Objekt der Klasse UpdateButtonController
         * @return Liefert ein Objekt der Klasse UpdateButtonController zurück (Konkatination möglich)
         */
        UpdateButtonController& operator= (const UpdateButtonController& aRhs);
};

#endif // UPDATEBUTTONCONTROLLER_H
