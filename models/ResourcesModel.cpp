#include "ResourcesModel.h"

#include "models/Model.h"

#include <QPxCore/QPxDeleter.h>

#include <QtGui/QPixmap>

namespace
{

class Item
{
public:
    Item(int index, const QString &text) : index(index), text(text) { }

    int index;
    QString text;
};

}

ResourcesModel::ResourcesModel(Model *model, QObject *parent) : QPx::TreeModel(parent), model(model)
{
    types[Entity::Type::DiffuseMap] = rowCount();
    appendRow(new Item(-1, "Textures"));

    types[Entity::Type::NormalMap] = rowCount();
    appendRow(new Item(-1, "Normal Maps"));

    types[Entity::Type::Model] = rowCount();
    appendRow(new Item(-1, "Models"));

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));
    modelChanged();

    setUserDataDeleter(new QPx::Deleter<Item>(this));
}

int ResourcesModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ResourcesModel::data(const QModelIndex &index, int role) const
{
    if(auto item = static_cast<const Item*>(userData(index)))
    {
        if(role == Qt::DisplayRole)
        {
            return item->text;
        }
        else if(role == Qt::DecorationRole)
        {
            if(item->index >= 0)
            {
                auto e = model->entities()[item->index];

                if(e.properties().contains("Thumbnail"))
                {
                    return e.property("Thumbnail").value<QPixmap>().scaledToHeight(16, Qt::SmoothTransformation);
                }
            }
        }
    }

    return QVariant();
}

int ResourcesModel::itemIndex(const QModelIndex &index) const
{
    if(auto item = static_cast<const Item*>(userData(index)))
    {
        return item->index;
    }

    return -1;
}

Entity::Type ResourcesModel::itemType(const QModelIndex &index) const
{
    if(auto item = static_cast<const Item*>(userData(index)))
    {
        if(item->index >= 0)
        {
            return model->entities()[item->index].type();
        }

        return types.keys()[index.row()];
    }

    return Entity::Type::Invalid;
}

void ResourcesModel::modelChanged()
{
    for(auto type: types.keys())
    {
        auto parent = index(types[type], 0);
        while(rowCount(parent))
        {
            removeRow(0, parent);
        }
    }

    for(int i: model->resources())
    {
        auto e = model->entities()[i];

        auto parent = index(types[e.type()], 0);
        appendRow(new Item(i, e.property("Path").value<QString>()), parent);
    }
}
