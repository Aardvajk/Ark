#include "ModelData.h"

#include "entity/EntityFactory.h"

#include "core/Mesh.h"

#include <GxMaths/GxVector.h>

#include <QtGui/QColor>
#include <QtCore/QPoint>

namespace
{

void randomise(Entity &e, const Mesh &m)
{
    for(int i = 0; i < m.faces.count(); ++i)
    {
        e.addSubProperty(Element::Type::Face, i, "Color", Property(QColor(std::rand() % 255, std::rand() % 255, std::rand() % 255)));
    }
}

}

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Name"] = Property("Model");
    properties["Background"] = Property(QColor(200, 220, 240));
    properties["Grid"] = Property(1.0f);

    auto m = Mesh::cuboid({ 2, 2, 2 });
    auto e = EntityFactory::create(Entity::Type::Geometry);

//    e.setMesh(m);
//    randomise(e, m);

//    entities.append(e);

//    e = EntityFactory::create(Entity::Type::Geometry);
//    e.setMesh(m.moved({ 3, 1, 3 }));
//    randomise(e, m);

//    entities.append(e);

//    e = EntityFactory::create(Entity::Type::Geometry);
//    e.setMesh(m.moved({ -3, 1, 3 }));
//    randomise(e, m);

//    entities.append(e);

//    e = EntityFactory::create(Entity::Type::Geometry);
//    e.setMesh(m.moved({ 0, -1, -3 }));
//    e.setMesh(Mesh::cuboidFromCorners(Gx::Vec3(-1, -1, -1), Gx::Vec3(1, 1, 1)));
//    randomise(e, m);

//    entities.append(e);
}
