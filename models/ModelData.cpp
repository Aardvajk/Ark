#include "ModelData.h"

#include "entity/EntityFactory.h"

#include "core/Mesh.h"

#include <GxMaths/GxVector.h>

#include <QtGui/QColor>
#include <QtCore/QPoint>

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    properties["Name"] = Property("Model");
    properties["Background"] = Property(QColor(200, 220, 240));
    properties["Grid"] = Property(1.0f);
    properties["Cursor"] = Property(Gx::Vec3(0, 0, 0));
}
