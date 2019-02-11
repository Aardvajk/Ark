#ifndef MODELDATA_H
#define MODELDATA_H

#include "properties/PropertyMap.h"

#include "entity/Entity.h"

#include <QtCore/QObject>
#include <QtCore/QVector>

class Entity;

class ModelData : public QObject
{
    Q_OBJECT

public:
    explicit ModelData(QObject *parent = nullptr);

    bool save(const QString &path) const;
    bool load(const QString &path);

    PropertyMap properties;
    QVector<Entity> entities;
};

#endif // MODELDATA_H
