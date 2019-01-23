#include "Entity.h"

#include "physics/Mesh.h"

#include "entity/EntityFactory.h"

namespace
{

const char *types[] = { "Geometry" };

}

Entity::Entity(Type type) : s(type, PropertyMap(), SubPropertyMap(), Mesh())
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

Mesh &Entity::mesh()
{
    return s.value().mesh;
}

const Mesh &Entity::mesh() const
{
    return s.value().mesh;
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

