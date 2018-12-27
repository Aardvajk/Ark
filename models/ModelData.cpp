#include "ModelData.h"

#include "entity/EntityFactory.h"

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Background"].setValue(QColor(20, 40, 60));

    auto e = EntityFactory::create(Entity::Type::Geometry);

    e.properties()["Mesh"].setValue(Mesh::cuboid({ 2, 2, 2 }));
    EntityFactory::updateMesh(e);

    e.properties()["Selection"].setValue(Selection(true));

    entities.append(e);
}
