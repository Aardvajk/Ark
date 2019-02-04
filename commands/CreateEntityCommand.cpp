#include "CreateEntityCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

CreateEntityCommand::CreateEntityCommand(const QString &name, const Entity &entity, Model *model) : Command(name, model), v(entity)
{
    redo();
}

bool CreateEntityCommand::isValid() const
{
    return true;
}

bool CreateEntityCommand::modifiesPersistentState() const
{
    return true;
}

void CreateEntityCommand::undo()
{
    v = data->entities.back();
    data->entities.pop_back();

    model->change();
}

void CreateEntityCommand::redo()
{
    if(v)
    {
        data->entities.append(*v);
        v = { };

        model->change();
    }
}

Entity CreateEntityCommand::entity() const
{
    return data->entities.back();
}

void CreateEntityCommand::update(const Entity &entity)
{
    data->entities.back() = entity;
    model->change();
}
