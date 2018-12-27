#ifndef MODELDATA_H
#define MODELDATA_H

#include "entity/Entity.h"

#include <QtCore/QObject>
#include <QtCore/QList>

class ModelData : public QObject
{
    Q_OBJECT

public:
    explicit ModelData(QObject *parent = nullptr);

    PropertyMap properties;
    QList<Entity> entities;
};

#endif // MODELDATA_H
