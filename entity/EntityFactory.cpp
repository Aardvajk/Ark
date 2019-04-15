#include "EntityFactory.h"

#include "properties/custom/TextureData.h"

#include "properties/Property.h"

#include <QtGui/QColor>
#include <QtGui/QPixmap>

#include <QtCore/QPoint>

Entity EntityFactory::create(Entity::Type type)
{
    Entity e(type);

    if(type == Entity::Type::Geometry)
    {
        e.addProperty("Name", Property("Geometry"));
        e.addProperty("Group", Property(QString()));
    }
    else if(Entity::isResourceType(type))
    {
        e.addProperty("Path", Property(QString()));
        e.addProperty("Thumbnail", Property(QPixmap()));
    }

    return e;
}

void EntityFactory::defaultFaceProperties(PropertyMap &properties)
{
    properties["Color"] = Property(QColor(200, 200, 200));
    properties["Visible"] = Property(true);
    properties["Texture"] = Property(TextureData());
}
