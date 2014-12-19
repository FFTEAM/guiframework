#ifndef SELECTIONMODEL_H
#define SELECTIONMODEL_H

#include <QAbstractListModel>
#include <QDebug>

class SelectionModel: public QAbstractListModel
{
    public:

        /**
         * @brief SelectionModel Constructor
         */
        explicit SelectionModel(QObject* aParent = 0);

        /**
         * @brief The SelectionRoles enum
         *
         * In diesem enum werden die Rollen definiert, welche später für die Kommunikation mit
         * der View verwendet werden.
         */
        enum SelectionRoles
        {
            SELECTION_VALUE_ROLE,            /**< Aktueller Wert für die Auswahl */
        };

        /**
         * @brief data Liefert der View die zur jeweiligen Rolle gehörenden Daten
         * @param aIndex Index aktuellen Model
         * @param aRole Aktuelle Rolle
         * @return Liefert ein Wertepaar (Rolle,Wert) zurück
         */
        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        /**
         * @brief rowCount Liefert die aktuelle Anzahl der Einträge im Model zurück
         * @param aParent -
         * @return Anzahl der Einträge
         */
        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        /**
         * @brief NewSelectionModel Fügt eine neue Menge an Datenobjekten dem Model hinzu
         * @param aSelectionModel Liste mit neuen Datenobjekten
         */
        void setNewSelectionModel(QList<QString>& aSelectionModel);

    protected:

        /**
         * @brief roleNames Verbindet die Rollen und die dazugehrigen Attribute der Klasse
         * @return QHash mit der Zuweisung der Rollen von der View und der Klasse
         *
         * Diese Methode wird ebenfalls vom Model/View Konzept von QT verwendet.
         */
        QHash<int, QByteArray> roleNames() const;

    private:

        QList<QString> m_dataList;

};

#endif // SELECTIONMODEL_H
