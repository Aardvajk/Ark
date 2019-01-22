#include "Model.h"

#include "models/ModelData.h"
#include "models/ModelBuffers.h"
#include "models/ModelCache.h"

#include "commands/Command.h"

namespace
{

class Cache
{
public:
    Cache(Model *model, Graphics *graphics) : data(new ModelData(model)), buffers(new ModelBuffers(model, graphics, model)), cache(new ModelCache(model, model)) { }

    ModelData *data;
    ModelBuffers *buffers;
    ModelCache *cache;
};

}

Model::Model(Graphics *graphics, QObject *parent) : QPx::AbstractEditorModel(parent)
{
    cache.alloc<Cache>(this, graphics);
}

void Model::beginCommand(Command *command)
{
    command->data = cache.get<Cache>().data;
}

QStringList Model::properties() const
{
    return cache.get<Cache>().data->properties.keys();
}

Property Model::property(const QString &name) const
{
    return cache.get<Cache>().data->properties[name];
}

void Model::addProperty(const QString &name, const Property &property)
{
    auto &p = cache.get<Cache>().data->properties;

    p[name] = property;
    p.invalidate();
}

const QVector<Entity> &Model::entities() const
{
    return cache.get<Cache>().data->entities;
}

Entity &Model::entity(int index)
{
    return cache.get<Cache>().data->entities[index];
}

Entity Model::entity(int index) const
{
    return cache.get<Cache>().data->entities[index];
}

const ModelBuffers *Model::buffers() const
{
    return cache.get<Cache>().buffers;
}

QVector<int> Model::selected() const
{
    return cache.get<Cache>().cache->selected();
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

void Model::change()
{
    emit changed();
}

void Model::setPropertyVariant(const QString &name, const QVariant &value)
{
    cache.get<Cache>().data->properties[name].setValue(value);
}
