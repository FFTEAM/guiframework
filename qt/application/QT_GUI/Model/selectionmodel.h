//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selcetionmodel.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  Include all declarations from SelectionModel
  *
  */

#ifndef SELECTIONMODEL_H
#define SELECTIONMODEL_H

#include <QAbstractListModel>
#include <QDebug>

/**
 * @brief The SelectionModel class This class represents a model for comboboxes.
 *
 *  All values from comboboxes are store in a data list from this class.
 *
 */
class SelectionModel: public QAbstractListModel
{
    public:

        /**
         * @brief SelectionModel Constructor to init all attributes
         * @param aParent Pointer to QAbstractListModel parent class
         */
        explicit SelectionModel(QObject* aParent = 0);

        /**
         * @brief The SelectionRoles enum Inlcude all roles from model
         */
        enum SelectionRoles
        {
            SELECTION_VALUE_ROLE,   /**< Role for a single value in combobox */
        };

        /**
         * @brief data Return to a index and role a QVariant value for view
         * @param aIndex Index of model
         * @param aRole Current Role
         * @return QVariant value with value and role
         *
         * This function is used by model/view on QT
         */
        QVariant data(const QModelIndex & aIndex, int aRole = Qt::DisplayRole) const;

        /**
         * @brief rowCount Actual count of rows in model
         * @param aParent -
         * @return Count of rows in model
         *
         * This function is used by model/view on QT
         */
        int rowCount(const QModelIndex & aParent = QModelIndex()) const;

        /**
         * @brief setNewSelection Model Add a new list of data objects to model
         * @param aSensorModel List with new data objects
         */
        void setNewSelectionModel(QList<QString>& aSelectionModel);

    protected:

        /**
         * @brief roleNames Connect Roles on view with roles in model
         * @return QHash with the connected roles
         *
         * This function is used by model/view on QT
         */
        QHash<int, QByteArray> roleNames() const;

    private:

        /**
         * @brief m_dataList QList with values for combobox on view
         */
        QList<QString> m_dataList;
};

#endif // SELECTIONMODEL_H
