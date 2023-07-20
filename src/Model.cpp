#include "inc/Model.h"
#include "inc/TreeItemData.h"

#include <QStringList>

Model::Model(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{

    // This would serve as a "Header" if we chose to show the tree as a table with more columns
    QVariant rootData("Item");
    rootItem = new TreeItem(rootData);

    // Initialize tree model based on input data
    setupData(data.split('\n'), rootItem);

    // Initialize role names
    m_roleNameMap[ModelRoleItem] = "item";
}

Model::~Model()
{
    delete rootItem;
}

QModelIndex Model::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    if (role == ModelRoleItem)
        return item->data(0);
    
    return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

     return QAbstractItemModel::flags(index);
}


QModelIndex Model::index(
    int row, int column, const QModelIndex& parent
) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

int Model::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem;

    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int Model::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();

    return rootItem->columnCount();
}

QHash<int, QByteArray> Model::roleNames() const
{
    return m_roleNameMap;
}

QVariant Model::newTreeItemData(const QString& text, int indentation, const QString& type, bool isClickable)
{
    TreeItemData* itemData = new TreeItemData(this);
    itemData->setText(text);
    itemData->setIndentation(indentation);
    itemData->setType(type);  // automatically translates to an icon
    itemData->setClickable(isClickable);

    QVariant variant;
    variant.setValue(itemData); // variant takes ownership of itemData

    return variant;
}

void Model::setupData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) 
    {
        int position = 0;
        // Figure out the indentation of the current line.
        while (position < lines[number].length())
        {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        // Read line contents and remove any trailing whitespace.
        QString lineData = lines[number].mid(position).trimmed();

        // Parse read line
        if (!lineData.isEmpty()) 
        {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split(": ", Qt::SkipEmptyParts);

            if (columnStrings.count() < 1) 
            {
                // Incomplete line or not formatted as expected.
                continue;
            }

            QString type = columnStrings[0];
            QString text = columnStrings[1];

            // qDebug() << "type: " << type << " text: " << text;

            // Create data item
            QVariant itemData;
            itemData = newTreeItemData(text, position, type);

            if (position > indentations.last()) 
            {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.
                if (parents.last()->childCount() > 0) 
                {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } 
            else 
            {
                while (position < indentations.last() && parents.count() > 0) 
                {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->append(new TreeItem(itemData, parents.last()));
        }

        ++number;
    }

    // Remove any remaining indented parents
    while (indentations.last() > 0 && parents.count() > 0)
    {
        parents.pop_back();
        indentations.pop_back();
    }

    // Add two buttons at the end of the tree
    QVariant itemData;
    itemData = newTreeItemData("User Profile", 0, "category", true);
    parents.last()->append(new TreeItem(itemData, parents.last()));

    itemData = newTreeItemData("Help", 0, "category", true);
    parents.last()->append(new TreeItem(itemData, parents.last()));
}
