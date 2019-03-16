#include "TextureDataPropertyBrowserType.h"

#include "properties/types/VecPropertyBrowserType.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

namespace
{

QVector<QVariant> values(const QVariant &value)
{
    if(value.isValid())
    {
        auto d = value.value<TextureData>();

        return { QVariant::fromValue(d.scale), QVariant::fromValue(d.offset) };
    }

    return { QVariant(), QVariant() };
}

}

TextureDataPropertyBrowserType::TextureDataPropertyBrowserType(QObject *parent) : QPx::PropertyBrowserType(parent)
{
    type = new Vec2PropertyBrowserType(this);
}

void TextureDataPropertyBrowserType::addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const
{
    auto v = values(item->value());

    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "Scale", item->flags(), v[0], item));
    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "Offset", item->flags(), v[1], item));

    for(auto i: item->items())
    {
        connect(i, SIGNAL(valueChanged(QVariant)), SLOT(changed(QVariant)));
    }
}

void TextureDataPropertyBrowserType::updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const
{
    auto v = values(value);

    item->items()[0]->setValue(v[0]);
    item->items()[1]->setValue(v[1]);
}

QString TextureDataPropertyBrowserType::valueText(const QPx::PropertyBrowserItem *item) const
{
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
            case 0: v.scale = value.value<Gx::Vec2>(); break;
            case 1: v.offset = value.value<Gx::Vec2>(); break;
        }

        auto var = QVariant::fromValue(v);

        parent->setValue(var);
        updateProperties(parent, var);
    }
}
