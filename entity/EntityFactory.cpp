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
    }

    return e;
}

void EntityFactory::defaultFaceProperties(PropertyMap &properties)
{
    properties["Color"] = Property(QColor(200, 200, 200));
    properties["Visible"] = Property(true);
}
