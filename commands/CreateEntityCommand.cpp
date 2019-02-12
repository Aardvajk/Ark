#include "CreateEntityCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

CreateEntityCommand::CreateEntityCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool CreateEntityCommand::isValid() const
{
    return !v.isEmpty();
}

bool CreateEntityCommand::modifiesPersistentState() const
{
    return true;
}

void CreateEntityCommand::undo()
{
    for(int i = v.count() - 1; i >= 0; --i)
    {
        v[i] = data->entities.back();
        data->entities.pop_back();
    }

    model->change();
}

void CreateEntityCommand::redo()
{
    for(int i = 0; i < v.count(); ++i)
    {
        data->entities.append(v[i]);
        v[i] = Entity();
    }

    model->change();
}

void CreateEntityCommand::create(const Entity &entity)
{
    v.append(entity);
}
