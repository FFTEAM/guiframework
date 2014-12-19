//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   customplotlinechart.h
  * @author Patrick Mathias, Markus Nebel
  * @author Verantwortlichkeit: Patrick Mathias
  * @date   12.12.2014 14:15:33 GMT
  *
  * @brief Diese Header-Datei enhält alle Deklarationen der Klasse CustomPlotLineChart
  *
  */

#ifndef CUSTOMPLOTLINECHART_H
#define CUSTOMPLOTLINECHART_H

#include <QPainter>
#include <QtQuick>
#include "Thirdparty/qcustomplot.h"
#include "Model/Data/sensordata.h"

/**
 * @brief The CustomPlotBarChart class
 *
 * Diese Klasse generiert ein Liniendiagramm zur Darstellung der Messdaten einer Belastungsmessung.
 * Diesbezüglich wird das third_party Produkt qCustomPlot verwendet. Diese Klasse wird im späteren
 * Verlauf als QML Komponente registriert und verwendet.
 */
class CustomPlotLineChart: public QQuickPaintedItem
{
    Q_OBJECT

    public:

        /**
         * @brief CustomPlotLineChart ist der Standardtkonstruktor der Klasse CustomPlotLineChart
         * @param aParent Zeiger auf die Basisklasse QObject
         */
        CustomPlotLineChart(QQuickItem* aParent = 0);

        /**
         * @brief ~CustomPlotLineChart ist der Desktruktor der Klasse ~CustomPlotLineChart
         */
        virtual ~CustomPlotLineChart ();

        /**
         * @brief paint Zeichnet auf Grundlage der Messdaten ein entsprechdes Diagramm
         * @param aPainter QPainter Objekt zum Zeichnen des Diagramms
         *
         * Diese Methode muss vom Entwickler neu implementiert werden.
         */
        void paint(QPainter* aPainter);

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

    private:

        /**
         * @brief CustomPlotLineChart Nicht in Verwendung (Definition fehlt)
         * @param aOther Referenz auf ein Objekt der Klasse CustomPlotLineChart
         */
        CustomPlotLineChart(const CustomPlotLineChart& aOther);

        /**
         * @brief operator = Nicht in Verwendung (Definition fehlt)
         * @param aRhs Referenz auf ein Objekt der Klasse CustomPlotLineChart
         * @return Liefert ein Objekt der Klasse CustomPlotLineChart zurück (Konkatination möglich)
         */
        CustomPlotLineChart& operator= (const CustomPlotLineChart& aRhs);


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
        QCPLineEnding* m_lineChart;

        /**
         * @brief updateCustomPlotSize Aktualisiert die Größe des Diagramms
         */
        void updateCustomPlotSize();

        /**
         * @brief calculateData Berechnet anhand der Sensordaten des Models die Diagrammwerte
         */
        void calculateData();

};

#endif // CUSTOMPLOTLINECHART_H
