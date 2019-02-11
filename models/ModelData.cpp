#include "ModelData.h"

#include "entity/EntityFactory.h"

#include "core/Mesh.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QFile>
#include <QtCore/QDataStream>

#include <QtGui/QColor>

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Name"] = Property("Model");
    properties["Background"] = Property(QColor(200, 220, 240));
    properties["Grid"] = Property(1.0f);
    properties["Cursor"] = Property(Gx::Vec3(0, 0, 0));
}

bool ModelData::save(const QString &path) const
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QDataStream ds(&file);

    ds << 1 << properties;

    ds << entities.count();
    for(auto &e: entities)
    {
        ds << e;
    }

    return true;
}

bool ModelData::load(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QDataStream ds(&file);

    int version;
    ds >> version;

    ds >> properties;

    int n;
    ds >> n;

    for(int i = 0; i < n; ++i)
    {
        Entity e;
        ds >> e;

        entities.append(e);
    }

    return true;
}
