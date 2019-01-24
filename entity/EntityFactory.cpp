#include "EntityFactory.h"

#include "properties/Property.h"

#include <QtGui/QColor>
#include <QtCore/QPoint>

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
static int xx = 0;

        e.addProperty("Name", Property("Geometry"));
if(xx == 1)
{
    e.addProperty("Burble", Property(QPoint(55,23)));
}
if(xx == 2)
{
    e.addProperty("Temp", Property(QPoint(88, 11)));
}
++xx;
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
