#include "CreateModel.h"

namespace
{

class Item
{
public:
    Item(int id, const QString &text) : id(id), text(text) { }

    int id;
    QString text;
};

}

CreateModel::CreateModel(QObject *parent) : QPx::TreeModel(parent)
{
    auto prims = appendRow(new Item(-1, "Primitives"));
    appendRow(new Item(0, "Cuboid"), prims);
    appendRow(new Item(1, "Sphere"), prims);
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
