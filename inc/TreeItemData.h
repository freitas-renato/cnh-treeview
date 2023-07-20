#ifndef _TREE_ITEM_DATA_H_
#define _TREE_ITEM_DATA_H_

#include <QObject>
#include <QHash>
#include <QString>

/*!
    Data structure to hold the data for a tree item.
*/
class TreeItemData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation NOTIFY indentationChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)

public:
    explicit TreeItemData(QObject* parent = nullptr);
    TreeItemData(const TreeItemData& other);
    ~TreeItemData();

    QString text();
    void setText(const QString& text);

    int indentation();
    void setIndentation(int indentation);

    QString icon();
    void setIcon(const QString& icon);

    QString type();
    void setType(const QString& type);

signals:
    void textChanged();
    void indentationChanged();
    void iconChanged();

private:
    QString m_text;
    int m_indentation;
    QString m_type;
    QString m_icon;

    // Hash map to map the type to an icon, if there is any.
    const QHash<QString, QString> iconMap = {
        { "category", "" },  // No Icon
        { "grower", "qrc:/assets/farmer.png" },
        { "farm", "qrc:/assets/barn.png" },
        { "field", "qrc:/assets/field.png" },
        { "tasks", "qrc:/assets/tasks.png" },
        { "task", "" },  // No Icon
        { "products", "qrc:/assets/products.png" },
        { "seed", "qrc:/assets/seeds.png" },
        { "plant", "qrc:/assets/roots.png" },
        { "product", "qrc:/assets/fertilizer.png" }
    };
};

Q_DECLARE_METATYPE(TreeItemData)


#endif  // _TREE_ITEM_DATA_H_
