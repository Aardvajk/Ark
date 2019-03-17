#include "PropertyTypeFactory.h"

#include "properties/types/VecPropertyBrowserType.h"
#include "properties/types/TextureDataPropertyBrowserType.h"
#include "properties/types/PathPropertyBrowserType.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserType.h>

#include <QGxMaths/QGxMathsMetatypes.h>

#include <stdexcept>

namespace
{

class Cache
{
public:
    QMap<int, QPx::PropertyBrowserType*> types;

    PathPropertyBrowserType *pathType;
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
    c.types[QMetaType::QPoint] = new QPx::PointPropertyBrowserType(this);
    c.types[qMetaTypeId<Gx::Vec2>()] = new Vec2PropertyBrowserType(this);
    c.types[qMetaTypeId<Gx::Vec3>()] = new Vec3PropertyBrowserType(this);
    c.types[qMetaTypeId<TextureData>()] = new TextureDataPropertyBrowserType(this);

    c.pathType = new PathPropertyBrowserType(this);
}

QPx::PropertyBrowserType *PropertyTypeFactory::type(int typeId, Property::SubType subType) const
{
    auto &c = cache.get<Cache>();

    if(subType == Property::SubType::Directory)
    {
        return c.pathType;
    }

    auto &t = c.types;

    auto i = t.find(typeId);
    if(i == t.end())
    {
        throw std::runtime_error("property type id not found");
    }

    return i.value();
}
