#ifndef MODELDATA_H
#define MODELDATA_H

#include "entity/Entity.h"

#include <QtCore/QList>

class ModelData
{
public:
    ModelData() = default;

    PropertyMap properties;
    QList<Entity> entities;
};

#endif // MODELDATA_H
