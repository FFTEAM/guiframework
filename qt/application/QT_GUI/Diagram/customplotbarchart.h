//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotbarchart.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#ifndef CUSTOMPLOTBARCHART_H
#define CUSTOMPLOTBARCHARTM_H

#include "Thirdparty/qcustomplot.h"
#include "Model/sensormodel.h"
#include <QtQuick>
#include <QPainter>
#include <QColor>
#include <QVector>

/** Konstante für die maximale erfassbare Herzfrequenz */
const int MAX_HEARTRATE = 230;

/**
 * @brief The CustomPlotBarChart class
 *
 * Diese Klasse generiert ein Balkendiagramm zur Darstellung der Messdaten einer Ruheplusmessung.
 * Diesbezüglich wird das third_party Produkt qCustomPlot verwendet. Diese Klasse wird im späteren
 * Verlauf als QML Komponente registriert und verwendet.
 */
class CustomPlotBarChart : public QQuickPaintedItem
{
    Q_OBJECT

    public:

        Q_PROPERTY(SensorModel* data READ getData WRITE setData)

        void setData(SensorModel*);

        SensorModel* getData();

        /**
         * @brief CustomPlotBarChart ist der Standardtkonstruktor der Klasse CustomPlotBarChart
         * @param aParent Zeiger auf die Basisklasse QObject
         */
        CustomPlotBarChart (QQuickItem* aParent = 0);

        /**
         * @brief ~CustomPlotBarChart ist der Desktruktor der Klasse CustomPlotBarChart
         */
        virtual ~CustomPlotBarChart ();

        /**
         * @brief initCustomPlot Initialistert das Diagramm und legt die Skalierung fest
         *
         * Diese Methode wird von der View automatisch aufgerufen, um das Diagramm zu initialisieren
         */
        Q_INVOKABLE void initCustomPlot();

        /**
         * @brief updateDataAndGUI Löscht das veraltete Diagramm und erzuegt ein neues Diagramm
         *
         * Diese Methode wird von der View automatisch aufgerufen, um das Diagramm zu aktualisieren
         */
        Q_INVOKABLE void updateDataAndGUI();

        /**
         * @brief paint Zeichnet auf Grundlage der Messdaten ein entsprechdes Diagramm
         * @param aPainter QPainter Objekt zum Zeichnen des Diagramms
         *
         * Diese Methode muss vom Entwickler neu implementiert werden.
         */
        void paint(QPainter* aPainter);

    private:

        /**
         * @brief m_inactiveModel pointer to inactiveModel to update diagram with current values
         */
        SensorModel* m_inactiveModel;

        /**
         * @brief CustomPlotBarChart Nicht in Verwendung (Definition fehlt)
         * @param aOther Referenz auf ein Objekt der Klasse CustomPlotBarChart
         */
        CustomPlotBarChart(const CustomPlotBarChart& aOther);

        /**
         * @brief operator = Nicht in Verwendung (Definition fehlt)
         * @param aRhs Referenz auf ein Objekt der Klasse CustomPlotBarChart
         * @return Liefert ein Objekt der Klasse CustomPlotBarChart zurück (Konkatination möglich)
         */
        CustomPlotBarChart& operator= (const CustomPlotBarChart& aRhs);

        /**
         * @brief m_CustomPlot Enthält ein Objekt der Klasse QCustomPlot
         */
        QCustomPlot*    m_CustomPlot;

        /**
         * @brief m_xAxis Repräsentiert die Daten der X-Achse
         */
        QVector<double> m_xAxis;

        /**
         * @brief m_yAxis Repräsentiert die Daten der Y-Achse
         */
        QVector<double> m_yAxis;

        /**
         * @brief m_barChart Repräsentiert den Diagrammtyp
         */
        QCPBars* m_barChart;

        virtual void hoverMoveEvent(QHoverEvent * event);
        QCPItemText *textLabel;

        QVector<double> m_tickValueVector;

        QVector<QString> m_tickLabelVector;

        /**
         * @brief updateCustomPlotSize Aktualisiert die Größe des Diagramms
         */
        void updateCustomPlotSize();

        /**
         * @brief calculateData Berechnet anhand der Sensordaten des Models die Diagrammwerte
         */
        void calculateData();
    private slots:
        void calculateTicksAndLabels();
};

#endif // CUSTOMPLOTBARCHART_H
