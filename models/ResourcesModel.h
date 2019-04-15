#ifndef RESOURCESMODEL_H
#define RESOURCESMODEL_H

#include "entity/Entity.h"

#include <QPxCore/QPxTreeModel.h>

#include <QtCore/QMap>

class Model;

class ResourcesModel : public QPx::TreeModel
{
    Q_OBJECT

public:
    ResourcesModel(Model *model, QObject *parent = nullptr);

    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    int itemIndex(const QModelIndex &index) const;
    Entity::Type itemType(const QModelIndex &index) const;

private slots:
    void modelChanged();

private:
    Model *model;
    QMap<Entity::Type, int> types;
};

#endif // RESOURCESMODEL_H
