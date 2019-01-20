#include "EntityFactory.h"

#include "properties/Property.h"

#include "properties/custom/Selection.h"
#include "properties/custom/Mesh.h"

#include <QtGui/QColor>
#include <QtCore/QPoint>

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
static int xx = 0;

        e.properties()["Name"] = Property("Geometry");
if(xx == 1)
{
    e.properties()["Burble"] = Property(QPoint(55,23));
}
if(xx == 2)
{
    e.properties()["Temp"] = Property(QPoint(88, 11));
}
++xx;
        e.properties()["Selection"] = Property(Selection(), Property::Flag::NonPersistent | Property::Flag::Hidden);
        e.properties()["Mesh"] = Property(Mesh(), Property::Flag::Hidden);
    }

    return e;
}

void EntityFactory::defaultFaceProperties(PropertyMap &properties)
{
    properties["Color"] = Property(QColor(std::rand() % 256, std::rand() % 256, std::rand() % 256));
    properties["Visible"] = Property(true);
}
