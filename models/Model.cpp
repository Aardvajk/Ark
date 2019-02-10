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
    setUndoLimit(100);
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

const QVector<Entity> &Model::entities() const
{
    return cache.get<Cache>().data->entities;
}

const ModelBuffers *Model::buffers() const
{
    return cache.get<Cache>().buffers;
}

QVector<int> Model::selected() const
{
    return cache.get<Cache>().cache->selected();
}

QVector<int> Model::objects() const
{
    return cache.get<Cache>().cache->objects();
}

bool Model::clear()
{
    auto &c = cache.get<Cache>();

    delete c.data;
    c.data = new ModelData();

    emit changed();
    return true;
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
