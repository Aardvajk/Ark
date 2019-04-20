#include "Model.h"

#include "models/ModelData.h"
#include "models/ModelBuffers.h"
#include "models/ModelCache.h"
#include "models/TextureMap.h"
#include "models/ModelMap.h"

#include "commands/Command.h"

#include <pcx/scoped_ptr.h>

namespace
{

class Cache
{
public:
    Cache(Model *model, Graphics *graphics) : data(new ModelData(model)), buffers(new ModelBuffers(model, graphics, model)), cache(new ModelCache(model, model)),
                                              textures(new TextureMap(model, graphics, model)),
                                              models(new ModelMap(model, graphics, model)) { }

    ModelData *data;
    ModelBuffers *buffers;
    ModelCache *cache;
    TextureMap *textures;
    ModelMap *models;
};

}

Model::Model(Graphics *graphics, QObject *parent) : QPx::AbstractEditorModel(parent)
{
    cache.alloc<Cache>(this, graphics);
    setUndoLimit(100);
}

Model::~Model()
{
    delete cache.get<Cache>().textures;
    delete cache.get<Cache>().models;
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

QVector<int> Model::resources() const
{
    return cache.get<Cache>().cache->resources();
}

TextureMap &Model::textures()
{
    return *cache.get<Cache>().textures;
}

const TextureMap &Model::textures() const
{
    return *cache.get<Cache>().textures;
}

ModelMap &Model::models()
{
    return *cache.get<Cache>().models;
}

const ModelMap &Model::models() const
{
    return *cache.get<Cache>().models;
}

bool Model::clear()
{
    auto &c = cache.get<Cache>();

    delete c.data;
    c.data = new ModelData();

    c.textures->clear();

    emit changed();
    emit reset();

    return true;
}

bool Model::open(const QString &path)
{
    pcx::scoped_ptr<ModelData> data(new ModelData());

    if(data->load(path))
    {
        auto &c = cache.get<Cache>();

        auto old = c.data;
        c.data = data.release();

        delete old;

        c.textures->clear();

        for(int i = 0; i < entities().count(); ++i)
        {
            auto e = entities()[i];
            if(e.type() == Entity::Type::DiffuseMap || e.type() == Entity::Type::NormalMap)
            {
                c.textures->add(e.property("Path").value<QString>());
            }
            else if(e.type() == Entity::Type::Model)
            {
                c.models->add(e.property("Path").value<QString>());
            }
        }

        emit changed();
        emit reset();

        return true;
    }

    return false;
}

bool Model::save(const QString &path) const
{
    return cache.get<Cache>().data->save(path);
}

QString Model::filter() const
{
    return "Ark Files (*.ark);;Any Files (*.*)";
}

void Model::change()
{
    emit changed();
}
