#include "ModelData.h"

#include "entity/EntityFactory.h"

#include "properties/custom/Mesh.h"

#include <GxMaths/GxVector.h>

#include <QtGui/QColor>
#include <QtCore/QPoint>

namespace
{

void randomise(Entity &e, const Mesh &m)
{
    for(int i = 0; i < m.faces.count(); ++i)
    {
        e.subProperties()[Element::Type::Face][i]["Color"] = Property(QColor(std::rand() % 255, std::rand() % 255, std::rand() % 255));
    }
}

}

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Name"] = Property("Model");
    properties["Background"] = Property(QColor(200, 220, 240));
    properties["Position"] = Property(QVariant::fromValue(Gx::Vec3(7, 8, 9)));

    auto m = Mesh::cuboid({ 2, 2, 2 });

    auto e = EntityFactory::create(Entity::Type::Geometry);

    e.properties()["Mesh"].setValue(m);
    randomise(e, m);

    entities.append(e);

    e = EntityFactory::create(Entity::Type::Geometry);
    e.properties()["Mesh"].setValue(m.moved({ 3, 1, 3 }));
    randomise(e, m);

    entities.append(e);

    e = EntityFactory::create(Entity::Type::Geometry);
    e.properties()["Mesh"].setValue(m.moved({ -3, 1, 3 }));
    randomise(e, m);

    entities.append(e);

    e = EntityFactory::create(Entity::Type::Geometry);
    e.properties()["Mesh"].setValue(m.moved({ 0, -2, -3 }));
    randomise(e, m);

    entities.append(e);
}
