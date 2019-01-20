#include "VecPropertyBrowserType.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserItem.h>

#include <QGxMaths/QGxMathsMetatypes.h>

Vec3PropertyBrowserType::Vec3PropertyBrowserType(QObject *parent) : QPx::PropertyBrowserType(parent)
{
    type = new QPx::FloatPropertyBrowserType(this);
}

void Vec3PropertyBrowserType::addProperties(QPx::PropertyBrowserItem *item, QPx::PropertyBrowserModel *model, const QModelIndex &parent) const
{
    auto v = item->value().value<Gx::Vec3>();

    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "X", item->flags(), v.x, item));
    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "Y", item->flags(), v.y, item));
    item->addItem(new QPx::PropertyBrowserItem(type, model, parent, { }, "Z", item->flags(), v.z, item));

    for(auto i: item->items())
    {
        connect(i, SIGNAL(valueChanged(QVariant)), SLOT(changed(QVariant)));
    }
}

void Vec3PropertyBrowserType::updateProperties(QPx::PropertyBrowserItem *item, const QVariant &value) const
{
    auto v = item->value().value<Gx::Vec3>();

    item->items()[0]->setValue(v.x);
    item->items()[1]->setValue(v.y);
    item->items()[2]->setValue(v.z);
}

QString Vec3PropertyBrowserType::valueText(const QPx::PropertyBrowserItem *item) const
{
    if(item->value().isValid())
    {
        auto v = item->value().value<Gx::Vec3>();
        return QString("%1, %2, %3").arg(v.x).arg(v.y).arg(v.z);
    }

    return QString();
}

bool Vec3PropertyBrowserType::readOnly() const
{
    return true;
}

int Vec3PropertyBrowserType::userType() const
{
    return qMetaTypeId<Gx::Vec3>();
}

void Vec3PropertyBrowserType::changed(const QVariant &value)
{
    auto item = static_cast<QPx::PropertyBrowserItem*>(sender());
    auto parent = static_cast<QPx::PropertyBrowserItem*>(item->parent());

    auto v = parent->value().value<Gx::Vec3>();

    switch(parent->items().indexOf(item))
    {
        case 0: v.x = value.toFloat(); break;
        case 1: v.y = value.toFloat(); break;
        case 2: v.z = value.toFloat(); break;
    }

    parent->setValue(QVariant::fromValue(v));
}
