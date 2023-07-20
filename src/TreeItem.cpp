#include "inc/TreeItem.h"

TreeItem::TreeItem(const QVariant& data, TreeItem* parent)
{
    m_itemData = data;
    m_parent = parent;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_children);
}

void TreeItem::append(TreeItem* child)
{
    m_children.append(child);
}

TreeItem* TreeItem::child(int row)
{
    if (row < 0 || row >= m_children.size())
        return nullptr;
    
    return m_children.value(row);
}

int TreeItem::childCount() const
{
    return m_children.count();
}

int TreeItem::columnCount() const
{
    // This particular tree has only one column of data
    return m_COLUMN_COUNT;
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= columnCount())
        return QVariant();

    return m_itemData;
}

int TreeItem::row() const
{
    if (m_parent)
        return m_parent->m_children.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeItem* TreeItem::parent()
{
    return m_parent;
}