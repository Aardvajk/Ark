#include "CreateModel.h"

#include "models/Model.h"

#include "entity/Entity.h"

namespace
{

class Item
{
public:
    explicit Item(const QString &text) : text(text) { }

    QString text;
};

}

CreateModel::CreateModel(Model *model, QObject *parent) : QPx::TreeModel(parent), model(model)
{
    auto prims = appendRow(new Item("Primitives"));
    appendRow(new Item("Cuboid"), prims);
    appendRow(new Item("Wedge"), prims);

    appendRow(new Item("Models"));
    modelChanged();

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));
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

void CreateModel::modelChanged()
{
    QStringList models;
    for(auto i: model->resources())
    {
        auto e = model->entities()[i];
        if(e.type() == Entity::Type::Model)
        {
            models.push_back(e.property("Path").value<QString>());
        }
    }

    for(int i = 0; i < rowCount(); ++i)
    {
        auto parent = index(i, 0);
        if(parent.data(Qt::DisplayRole).toString() == "Models")
        {
            while(rowCount(parent))
            {
                removeRow(0, parent);
            }

            for(auto &m: models)
            {
                appendRow(new Item(m), parent);
            }

            break;
        }
    }
}
