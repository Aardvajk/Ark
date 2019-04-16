#include "TextureDataPropertyBrowserType.h"

#include "properties/types/TexturePropertyBrowserType.h"
#include "properties/types/VecPropertyBrowserType.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

namespace
{

QVector<QVariant> values(const QVariant &value)
{
    if(value.isValid())
    {
        auto d = value.value<TextureData>();

        return { QVariant::fromValue(d.diffuse), QVariant::fromValue(d.normal), QVariant::fromValue(d.scale), QVariant::fromValue(d.offset) };
    }

    return { QVariant(), QVariant(), QVariant(), QVariant() };
}

}

TextureDataPropertyBrowserType::TextureDataPropertyBrowserType(const Model *model, QObject *parent) : QPx::PropertyBrowserType(parent)
{
    diffuseType = new TexturePropertyBrowserType(model, Entity::Type::DiffuseMap, this);
    normalType = new TexturePropertyBrowserType(model, Entity::Type::NormalMap, this);
    vecType = new Vec2PropertyBrowserType(this);
}

void TextureDataPropertyBrowserType::addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const
{
    auto v = values(item->value());

    item->addItem(new QPx::PropertyBrowserItem(diffuseType, model, parent, { }, "Diffuse", item->flags(), v[0], item));
    item->addItem(new QPx::PropertyBrowserItem(normalType, model, parent, { }, "Normal", item->flags(), v[1], item));
    item->addItem(new QPx::PropertyBrowserItem(vecType, model, parent, { }, "Scale", item->flags(), v[2], item));
    item->addItem(new QPx::PropertyBrowserItem(vecType, model, parent, { }, "Offset", item->flags(), v[3], item));

    for(auto i: item->items())
    {
        connect(i, SIGNAL(valueChanged(QVariant)), SLOT(changed(QVariant)));
    }
}

void TextureDataPropertyBrowserType::updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const
{
    auto v = values(value);

    for(int i = 0; i < v.count(); ++i)
    {
        item->items()[i]->setValue(v[i]);
    }
}

QString TextureDataPropertyBrowserType::valueText(const QPx::PropertyBrowserItem *item) const
{
    auto v = values(item->value());
    if(v[0].isValid())
    {
        return v[0].toString();
    }

    return QString();
}

bool TextureDataPropertyBrowserType::readOnly() const
{
    return true;
}

int TextureDataPropertyBrowserType::userType() const
{
    return qMetaTypeId<TextureData>();
}

void TextureDataPropertyBrowserType::changed(const QVariant &value)
{
    if(value.isValid())
    {
        auto item = static_cast<QPx::PropertyBrowserItem*>(sender());
        auto parent = static_cast<QPx::PropertyBrowserItem*>(item->parent());

        auto v = parent->value().value<TextureData>();

        switch(parent->items().indexOf(item))
        {
            case 0: v.diffuse = value.value<QString>(); break;
            case 1: v.normal = value.value<QString>(); break;
            case 2: v.scale = value.value<Gx::Vec2>(); break;
            case 3: v.offset = value.value<Gx::Vec2>(); break;
        }

        auto var = QVariant::fromValue(v);

        parent->setValue(var);
        updateProperties(parent, var);
    }
}
