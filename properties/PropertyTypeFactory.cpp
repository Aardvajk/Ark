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

    PathPropertyBrowserType *exportType;
    PathPropertyBrowserType *directoryType;
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

    c.exportType = new PathPropertyBrowserType(PathPropertyBrowserType::Type::File, "Data Files (*.dat);;Any Files (*.*)", this);
    c.directoryType = new PathPropertyBrowserType(PathPropertyBrowserType::Type::Directory, QString(), this);
}

QPx::PropertyBrowserType *PropertyTypeFactory::type(int typeId, Property::SubType subType) const
{
    auto &c = cache.get<Cache>();

    switch(subType)
    {
        case Property::SubType::Export: return c.exportType;
        case Property::SubType::Directory: return c.directoryType;

        default: break;
    }

    auto &t = c.types;

    auto i = t.find(typeId);
    if(i == t.end())
    {
        throw std::runtime_error("property type id not found");
    }

    return i.value();
}
