#include "Model.h"

#include "models/ModelData.h"

Model::Model(QObject *parent) : QPx::AbstractEditorModel(parent), data(new ModelData())
{
}

Model::~Model()
{
    delete data;
}

const PropertyMap &Model::properties() const
{
    return data->properties;
}

const QList<Entity> &Model::entities() const
{
    return data->entities;
}

bool Model::clear()
{
    return false;
}

bool Model::open(const QString &path)
{
    return false;
}

bool Model::save(const QString &path) const
{
    return false;
}

QString Model::filter() const
{
    return "Ark Files (*.ark);;Any Files (*.*)";
}
