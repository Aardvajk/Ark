#include "EntityFactory.h"

#include "properties/Property.h"

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.properties()["Name"] = Property("Geometry");
        e.properties()["Mesh"] = Property(Mesh(), Property::Flag::Hidden);
    }

    return e;
}
