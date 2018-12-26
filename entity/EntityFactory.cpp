#include "EntityFactory.h"

#include "properties/Property.h"

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.properties()["Name"] = Property("Geometry");
        e.properties()["Selection"] = Property(Selection(), Property::Flag::Hidden | Property::Flag::NonPersistent);

        e.properties()["Mesh"] = Property(Mesh(), Property::Flag::Hidden);
    }

    return e;
}

void EntityFactory::updateMesh(Entity &entity)
{
    auto mesh = entity.properties()["Mesh"].toMesh();
    auto &faces = entity.subProperties()[Selection::Type::Face];

    faces.clear();
    for(int i = 0; i < mesh.faces.count(); ++i)
    {
        PropertyMap pm;

        pm["Color"] = Property(QColor(0, 0, 0));
        pm["Visible"] = Property(true);

        faces.append(pm);
    }
}
