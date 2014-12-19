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
