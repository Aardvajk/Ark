#include "EntityFactory.h"

#include "properties/Property.h"

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.properties()["Name"] = Property("Geometry");
        e.properties()["Mesh"] = Property(Mesh(), Property::Flag::Hidden);
        e.properties()["Selection"] = Property(Selection(), Property::Flag::NonPersistent | Property::Flag::Hidden);
    }

    return e;
}
