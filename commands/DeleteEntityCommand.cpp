#include "DeleteEntityCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"
#include "models/TextureMap.h"

DeleteEntityCommand::DeleteEntityCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool DeleteEntityCommand::isValid() const
{
    return !v.isEmpty();
}

bool DeleteEntityCommand::modifiesPersistentState() const
{
    return true;
}

void DeleteEntityCommand::undo()
{
    for(auto i: v.keys())
    {
        if(Entity::isResourceType(v[i].type()))
        {
            model->textures().add(v[i].property("Path").value<QString>());
        }

        data->entities.insert(data->entities.begin() + i, v[i]);
        v[i] = Entity();
    }

    model->change();
}

void DeleteEntityCommand::redo()
{
    auto keys = v.keys();
    for(int i = keys.count() - 1; i >= 0; --i)
    {
        int e = keys[i];

        v[e] = data->entities[e];
        data->entities.remove(e);

        if(Entity::isResourceType(v[e].type()))
        {
            model->textures().remove(v[e].property("Path").value<QString>());
        }
    }

    model->change();
}

void DeleteEntityCommand::remove(int index)
{
    v[index] = Entity();
}
