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

const PropertyMap &Model::properties() const
{
    return cache.get<Cache>().data->properties;
}

const QList<Entity> &Model::entities() const
{
    return cache.get<Cache>().data->entities;
}

const ModelBuffers *Model::buffers() const
{
    return cache.get<Cache>().buffers;
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
