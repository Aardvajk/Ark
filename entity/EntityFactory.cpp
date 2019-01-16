#include "EntityFactory.h"

#include "properties/Property.h"

#include "properties/custom/Selection.h"
#include "properties/custom/Mesh.h"

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.properties()["Name"] = Property("Geometry");
        e.properties()["Position"] = Property(Gx::Vec3());
        e.properties()["Selection"] = Property(Selection(), Property::Flag::NonPersistent | Property::Flag::Hidden);
        e.properties()["Mesh"] = Property(Mesh(), Property::Flag::Hidden);
    }

    return e;
}
