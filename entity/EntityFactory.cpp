#include "EntityFactory.h"

#include "properties/Property.h"

#include <QtGui/QColor>
#include <QtCore/QPoint>

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.addProperty("Name", Property("Geometry"));
        e.addProperty("Vec", Property(Gx::Vec3(1, 2, 3)));
        e.addProperty("Point", Property(QPoint(1, 2)));
    }

    return e;
}

void EntityFactory::defaultFaceProperties(PropertyMap &properties)
{
    properties["Color"] = Property(QColor(std::rand() % 256, std::rand() % 256, std::rand() % 256));
    properties["Visible"] = Property(true);
}
