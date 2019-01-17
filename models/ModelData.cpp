#include "ModelData.h"

#include "entity/EntityFactory.h"

#include "properties/custom/Mesh.h"

#include <GxMaths/GxVector.h>

#include <QtGui/QColor>

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Background"].setValue(QColor(200, 220, 240));

    auto m = Mesh::cuboid({ 2, 2, 2 });

    auto e = EntityFactory::create(Entity::Type::Geometry);
    e.properties()["Mesh"].setValue(m);

    e.properties()["Position"].setValue(Gx::Vec3(0, 0, 0));
    entities.append(e);

//    e.properties()["Position"].setValue(Gx::Vec3(3, 1, 3));
//    entities.append(e);

//    e.properties()["Position"].setValue(Gx::Vec3(-3, 1, 3));
//    entities.append(e);

//    e.properties()["Position"].setValue(Gx::Vec3(0, -2, -3));
//    entities.append(e);
}
