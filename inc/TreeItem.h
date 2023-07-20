#ifndef _TREEITEM_H_
#define _TREEITEM_H_

#include <QVariant>
#include <QList>

class TreeItem {
public:
    explicit TreeItem(const QVariant& data, TreeItem* parent = nullptr);
    ~TreeItem();

    void append(TreeItem* child);

    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parent();

private:
    static const int m_COLUMN_COUNT = 1;

    QList<TreeItem*> m_children;
    TreeItem* m_parent;

    QVariant m_itemData;
};

#endif  // _TREEITEM_H_