#include "Model.h"

Model::Model(QObject *parent) : QPx::AbstractEditorModel(parent)
{
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
