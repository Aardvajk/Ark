#include "PropertyModel.h"

#include "models/Model.h"

#include "properties/Property.h"
#include "properties/PropertyTypeFactory.h"

#include "properties/custom/Selection.h"

#include "entity/Entity.h"

#include "commands/ModifyPropertyCommand.h"

#include <QPxCore/QPxStdHash.h>

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>
#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

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

class Final
{
public:
    Final() = default;
    Final(const QVariant &value, int userType, QPx::PropertyBrowserItem::Flags flags) : value(value), userType(userType), flags(flags) { }

    QVariant value;
    int userType;
    QPx::PropertyBrowserItem::Flags flags;
};

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
    int total = 0;

    if(type == Element::Type::Model)
    {
        mergeProperties(model->properties(), merged);
        total = 1;
    }
    else if(type == Element::Type::Object)
    {
        for(auto i: model->selected())
        {
            mergeProperties(model->entities()[i].properties(), merged);
        }

        total = model->selected().count();
    }
    else
    {
        for(auto i: model->selected())
        {
            auto &entity = model->entities()[i];
            for(auto j: entity.properties()["Selection"].value<Selection>().elements[type])
            {
                mergeProperties(entity.subProperties()[type][j], merged);
                ++total;
            }
        }
    }

    pcx::ordered_map<QString, Final, QPx::StdHash > finals;

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
        int userType = value.userType();

        for(int i = 1; i < m.second.count(); ++i)
        {
            if(m.second[i].value<QVariant>().userType() != userType)
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

        if(!conflict && m.second.count() == total)
        {
            finals[m.first] = Final(value, userType, flags);
        }
    }

    QHash<QString, int> rows;
    for(int i = 0; i < rowCount(); ++i)
    {
        rows[static_cast<QPx::PropertyBrowserItem*>(userData(index(i, 0)))->name()] = i;
    }

    QSet<QString> valids;

    int insert = 0;
    for(auto m: finals)
    {
        auto row = rows.find(m.first);

        if(row == rows.end())
        {
            auto &value = m.second.value;

            connect(new QPx::PropertyBrowserItem(factory->type(m.second.userType), this, QModelIndex(), insert, m.first, m.second.flags, value, this), SIGNAL(valueChanged(QVariant)), SLOT(itemValueChanged(QVariant)));

            for(auto &r: rows)
            {
                if(r > insert) ++r;
            }

            ++insert;
        }
        else
        {
            auto item = static_cast<QPx::PropertyBrowserItem*>(userData(index(*row, 0)));

            if(item->flags() == m.second.flags && item->type()->userType() == m.second.userType)
            {
                item->setValue(m.second.value);
                item->type()->updateProperties(item, m.second.value);
            }
        }

        valids.insert(m.first);
    }

    for(int i = rowCount() - 1; i >= 0; --i)
    {
        auto item = static_cast<const QPx::PropertyBrowserItem*>(userData(index(i, 0)));

        if(!valids.contains(item->name()))
        {
            removeRow(i);
        }
    }
}

void PropertyModel::itemValueChanged(const QVariant &value)
{
    if(lock || !value.isValid()) return;

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