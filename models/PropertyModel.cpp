#include "PropertyModel.h"

#include "models/Model.h"

#include "properties/Property.h"
#include "properties/PropertyTypeFactory.h"

#include "properties/custom/Selection.h"

#include "entity/Entity.h"

#include "commands/ModifyPropertyCommand.h"

#include <QPxCore/QPxStdHash.h>

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

#include <pcx/ordered_map.h>

namespace
{

void mergeProperties(const PropertyMap &properties, pcx::ordered_map<QString, QVector<Property>, QPx::StdHash> &merged)
{
    for(auto &p: properties)
    {
        if(!(p.second.flags() & Property::Flag::Hidden))
        {
            merged[p.first].append(p.second);
        }
    }
}

}

PropertyModel::PropertyModel(Element::Type type, Model *model, PropertyTypeFactory *factory, QObject *parent) : QPx::PropertyBrowserModel(parent), type(type), model(model), factory(factory)
{
    connect(model, SIGNAL(changed()), SLOT(selectionChanged()));
    selectionChanged();
}

void PropertyModel::selectionChanged()
{
    if(lock) return;

    pcx::ordered_map<QString, QVector<Property>, QPx::StdHash> merged;

    if(type == Element::Type::Model)
    {
        mergeProperties(model->properties(), merged);
    }
    else if(type == Element::Type::Object)
    {
        for(auto i: model->selected())
        {
            mergeProperties(model->entities()[i].properties(), merged);
        }
    }
    else
    {
        for(auto i: model->selected())
        {
            auto &entity = model->entities()[i];
            for(auto j: entity.properties()["Selection"].value<Selection>().elements[type])
            {
                mergeProperties(entity.subProperties()[type][j], merged);
            }
        }
    }

    clear();

    for(auto &m: merged)
    {
        auto first = m.second[0];

        bool conflict = false;
        QPx::PropertyBrowserItem::Flags flags;

        if(first.flags() & Property::Flag::ReadOnly)
        {
            flags |= QPx::PropertyBrowserItem::Flag::ReadOnly;
        }

        QVariant value = first.value<QVariant>();
        for(int i = 1; i < m.second.count(); ++i)
        {
            if(m.second[i].value<QVariant>().userType() != value.userType())
            {
                conflict = true;
                break;
            }

            if(m.second[i].flags() & Property::Flag::ReadOnly)
            {
                flags |= QPx::PropertyBrowserItem::Flag::ReadOnly;
            }

            if(m.second[i].value<QVariant>() != value)
            {
                value = QVariant();
                break;
            }
        }

        if(!conflict)
        {
            connect(new QPx::PropertyBrowserItem(factory->type(first), this, QModelIndex(), m.first, flags, value, this), SIGNAL(valueChanged(QVariant)), SLOT(valueChanged(QVariant)));
        }
    }
}

void PropertyModel::valueChanged(const QVariant &value)
{
    auto s = pcx::scoped_lock(lock);

    auto item = static_cast<QPx::PropertyBrowserItem*>(sender());
    auto command = new ModifyPropertyCommand("Change Property", model);

    if(type == Element::Type::Model)
    {
        command->change(type, item->name(), -1, -1, value);
    }
    else if(type == Element::Type::Object)
    {
        for(auto i: model->selected())
        {
            command->change(type, item->name(), i, -1, value);
        }
    }
    else
    {
        for(auto i: model->selected())
        {
            for(auto j: model->entities()[i].properties()["Selection"].value<Selection>().elements[type])
            {
                command->change(type, item->name(), i, j, value);
            }
        }
    }

    model->endCommand(command);
}
