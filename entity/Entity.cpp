#include "Entity.h"

#include "core/Mesh.h"

#include "entity/EntityFactory.h"

namespace
{

const char *types[] = { "Geometry" };

}

Entity::Entity(Type type) : s(type, PropertyMap(), SubPropertyMap(), Selection(), Mesh())
{
    s.value().subProps[Element::Type::Face].setDefaultFunction(EntityFactory::defaultFaceProperties);
}

QStringList Entity::properties() const
{
    return s.value().props.keys();
}

QStringList Entity::subProperties(Element::Type type, int index) const
{
    auto r = s.value().subProps[type][index].keys();

    if(type == Element::Type::Vertex)
    {
        r.append("Position");
    }

    return r;
}

Property Entity::property(const QString &name) const
{
    return s.value().props[name];
}

void Entity::addProperty(const QString &name, const Property &property)
{
    auto &p = s.value().props;

    p[name] = property;
    p.invalidate();
}

Property Entity::subProperty(Element::Type type, int index, const QString &name) const
{
    if(type == Element::Type::Vertex && name == "Position")
    {
        return Property(s.value().mesh.vertices[index]);
    }

    return s.value().subProps[type][index][name];
}

void Entity::addSubProperty(Element::Type type, int index, const QString &name, const Property &property)
{
    auto &p = s.value().subProps[type][index];

    p[name] = property;
    p.invalidate();
}

const Selection &Entity::selection() const
{
    return s.value().selection;
}

void Entity::setSelection(const Selection &value)
{
    s.value().selection = value;
}

Mesh &Entity::mesh()
{
    return s.value().mesh;
}

const Mesh &Entity::mesh() const
{
    return s.value().mesh;
}

void Entity::setMesh(const Mesh &value)
{
    s.value().mesh = value;
}

const char *Entity::typeToString(Type type)
{
    return types[static_cast<int>(type)];
}

Entity::Type Entity::typeFromString(const std::string &text)
{
    int i = 0;
    while(types[i][0])
    {
        if(types[i] == text)
        {
            return static_cast<Type>(i);
        }

        ++i;
    }

    return Type::Invalid;
}

void Entity::saveToStream(QDataStream &ds) const
{
    ds << s.value().props << s.value().mesh;

    ds << s.value().subProps.keys().count();
    for(auto element: s.value().subProps.keys())
    {
        ds << element << s.value().subProps[element];
    }
}

void Entity::loadFromStream(QDataStream &ds)
{
    ds >> s.value().props >> s.value().mesh;

    int n;
    ds >> n;

    for(int i = 0; i < n; ++i)
    {
        Element::Type element;
        ds >> element;

        ds >> s.value().subProps[element];
    }
}

void Entity::setPropertyVariant(const QString &name, const QVariant &value)
{
    s.value().props[name].setValue(value);
}

void Entity::setSubPropertyVariant(Element::Type type, int index, const QString &name, const QVariant &value)
{
    if(type == Element::Type::Vertex && name == "Position" && value.userType() == qMetaTypeId<Gx::Vec3>())
    {
        s.value().mesh.vertices[index] = value.value<Gx::Vec3>();
    }
    else
    {
        s.value().subProps[type][index][name].setValue(value);
    }
}

QDataStream &operator<<(QDataStream &ds, const Entity &entity)
{
    ds << entity.type();

    entity.saveToStream(ds);
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Entity &entity)
{
    Entity::Type type;
    ds >> type;

    entity = EntityFactory::create(type);
    entity.loadFromStream(ds);

    return ds;
}
