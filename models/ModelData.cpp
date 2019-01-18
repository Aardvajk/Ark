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
    entities.append(e);

    e.properties()["Mesh"].setValue(m.moved({ 3, 1, 3 }));
    entities.append(e);

    e.properties()["Mesh"].setValue(m.moved({ -3, 1, 3 }));
    entities.append(e);

    e.properties()["Mesh"].setValue(m.moved({ 0, -2, -3 }));
    entities.append(e);
}
