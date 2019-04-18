#include "ModifyMeshCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

ModifyMeshCommand::ModifyMeshCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool ModifyMeshCommand::isValid() const
{
    return !v.isEmpty();
}

bool ModifyMeshCommand::modifiesPersistentState() const
{
    return true;
}

void ModifyMeshCommand::undo()
{
    for(auto i = v.begin(); i != v.end(); ++i)
    {
        data->entities[i.key()].setMesh(i.value().first);
    }

    model->change();
}

void ModifyMeshCommand::redo()
{
    for(auto i = v.begin(); i != v.end(); ++i)
    {
        data->entities[i.key()].setMesh(i.value().second);
    }

    model->change();
}

void ModifyMeshCommand::modify(int index, const Mesh &mesh)
{
    v[index] = qMakePair(data->entities[index].mesh(), mesh);
}
