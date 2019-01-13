#ifndef MODELDATA_H
#define MODELDATA_H

#include "entity/Entity.h"

#include <QPxCore/QPxStableList.h>

#include <QtCore/QObject>

class ModelData : public QObject
{
    Q_OBJECT

public:
    explicit ModelData(QObject *parent = nullptr);

    PropertyMap properties;
    QPx::StableList<Entity> entities;
};

#endif // MODELDATA_H
