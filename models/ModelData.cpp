#include "ModelData.h"

#include "entity/EntityFactory.h"

namespace
{

Mesh moveMesh(const Mesh &mesh, const Gx::Vec3 &distance)
{
    auto m = mesh;
    for(auto &v: m.vertices) v += distance;

    return m;
}

}

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Background"].setValue(QColor(200, 220, 240));

    auto e = EntityFactory::create(Entity::Type::Geometry);
    auto m = Mesh::cuboid({ 2, 2, 2 });

    e.properties()["Mesh"].setValue(m);
    entities.append(e);

    e.properties()["Mesh"].setValue(moveMesh(m, { 3, 1, 3}));
    entities.append(e);

    e.properties()["Mesh"].setValue(moveMesh(m, { -3, 1, 3}));
    entities.append(e);

    e.properties()["Mesh"].setValue(moveMesh(m, { 0, -2, -3}));
    entities.append(e);
}
