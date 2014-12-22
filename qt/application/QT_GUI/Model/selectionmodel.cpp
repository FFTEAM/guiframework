//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   selectionmodel.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Patrick Mathias
  * @date   12.12.2014 13:56:00 GMT
  *
  * @brief  ToDo
  *
  */

#include "selectionmodel.h"

SelectionModel::SelectionModel(QObject* aParent):QAbstractListModel(aParent)
{
    // C'tor
}


QVariant SelectionModel::data(const QModelIndex &aIndex, int aRole) const
{
    if (aIndex.row() < 0 || aIndex.row() >= m_dataList.count()) return QVariant();
    const QString value= m_dataList[aIndex.row()];

    switch(aRole)
    {
        case SELECTION_VALUE_ROLE:  return value; break;

        default:                    return QVariant();
    }
}

int SelectionModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);
    return m_dataList.count();
}

void SelectionModel::setNewSelectionModel(QList<QString>& aSelectionModel)
{
    beginResetModel();
    m_dataList = aSelectionModel;
    endResetModel();
}

QHash<int, QByteArray> SelectionModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[SELECTION_VALUE_ROLE]   = "selectionValue";

    return roles;
}
