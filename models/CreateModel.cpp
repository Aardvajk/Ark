#include "CreateModel.h"

namespace
{

class Item
{
public:
    explicit Item(const QString &text) : text(text) { }

    QString text;
};

}

CreateModel::CreateModel(QObject *parent) : QPx::TreeModel(parent)
{
    auto prims = appendRow(new Item("Primitives"));
    appendRow(new Item("Cuboid"), prims);
    appendRow(new Item("Wedge"), prims);
}

int CreateModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CreateModel::data(const QModelIndex &index, int role) const
{
    if(auto item = static_cast<const Item*>(userData(index)))
    {
        if(role == Qt::DisplayRole)
        {
            return item->text;
        }
    }

    return QVariant();
}
