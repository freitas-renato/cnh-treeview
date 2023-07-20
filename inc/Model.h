#include "TreeItem.h"

#include <QVariant>
#include <QModelIndex>
#include <QAbstractItemModel>

class Model : public QAbstractItemModel 
{
    Q_OBJECT

public:
    enum ModelRoles
    {
        ModelRoleItem = Qt::UserRole + 1,
        ModelRoleHasChildren
    };


    explicit Model(const QString& data, QObject* parent = nullptr);
    ~Model();

    /***** QAbstractItemModel class interface overrides ****/

    QModelIndex parent(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex index(
        int row, int column, const QModelIndex& parent = QModelIndex()
    ) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;


private:
    /**
     * @brief Creates a new object containing the actual data for a tree item.
     * 
     * @param text          Field description
     * @param indentation   Item indentation level inside the tree
     * @param type          Field type (used to determine the icon to display)
     * @return QVariant     The new data object
     */
    QVariant newTreeItemData(const QString& text, int indentation, const QString& type);

    /**
     * @brief Populates the model with data from content of a file.
     * 
     * @param data   The file content
     * @param parent Tree root
     */
    void setupData(const QStringList& data, TreeItem* parent);

    // Tree root
    TreeItem* rootItem;

    // Hash table for mapping role names to role enum values
    QHash<int, QByteArray> m_roleNameMap;
};