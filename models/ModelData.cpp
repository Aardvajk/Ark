#include "ModelData.h"

#include "entity/EntityFactory.h"

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Background"].setValue(QColor(200, 220, 250));

    auto e = EntityFactory::create(Entity::Type::Geometry);

    e.properties()["Mesh"].setValue(Mesh::cuboid({ 2, 2, 2 }));
    EntityFactory::updateMesh(e);

    entities.append(e);

    auto m = e.properties()["Mesh"].toMesh();
    for(auto &v: m.vertices)
    {
        v += Gx::Vec3(3, 1, 3);
    }

    e.properties()["Mesh"].setValue(m);

    entities.append(e);
}
