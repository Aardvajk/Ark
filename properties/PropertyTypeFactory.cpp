#include "PropertyTypeFactory.h"

#include "properties/Property.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

namespace
{

class Cache
{
public:
    QMap<int, QPx::PropertyBrowserType*> types;
};

}

PropertyTypeFactory::PropertyTypeFactory(QObject *parent) : QObject(parent)
{
    auto &c = cache.alloc<Cache>();

    c.types[QMetaType::QString] = new QPx::StringPropertyBrowserType(this);
    c.types[QMetaType::Int] = new QPx::IntPropertyBrowserType(this);
    c.types[QMetaType::Float] = new QPx::FloatPropertyBrowserType(this);
    c.types[QMetaType::Bool] = new QPx::BoolPropertyBrowserType(this);
    c.types[QMetaType::QColor] = new QPx::ColorPropertyBrowserType(this);
}

QPx::PropertyBrowserType *PropertyTypeFactory::type(const Property &property) const
{
    return cache.get<Cache>().types[property.value<QVariant>().userType()];
}
