#include "TextureDataPropertyBrowserType.h"

#include "properties/types/VecPropertyBrowserType.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

TextureDataPropertyBrowserType::TextureDataPropertyBrowserType(QObject *parent) : QPx::PropertyBrowserType(parent)
{
    type = new Vec2PropertyBrowserType(this);
}

void TextureDataPropertyBrowserType::addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const
{
    auto v = item->value().value<TextureData>();

    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "Scale", item->flags(), QVariant::fromValue(v.scale), item));

    for(auto i: item->items())
    {
        connect(i, SIGNAL(valueChanged(QVariant)), SLOT(changed(QVariant)));
    }
}

void TextureDataPropertyBrowserType::updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const
{
    auto v = value.value<TextureData>();

    item->items()[0]->setValue(QVariant::fromValue(v.scale));
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
            case 0: v.scale = value.value<Gx::Vec2>();
        }

        auto var = QVariant::fromValue(v);

        parent->setValue(var);
        updateProperties(parent, var);
    }
}
