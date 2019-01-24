#include "ModifySelectionCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

namespace
{

void update(Model *model, ModelData *data, const QHash<int, QPx::IndexedPair<Selection> > &v, int index)
{
    for(auto i = v.begin(); i != v.end(); ++i)
    {
        data->entities[i.key()].setSelection(i.value()[index]);
    }

    model->change();
}

}

ModifySelectionCommand::ModifySelectionCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool ModifySelectionCommand::isValid() const
{
    return !v.isEmpty();
}

bool ModifySelectionCommand::modifiesPersistentState() const
{
    return false;
}

void ModifySelectionCommand::undo()
{
    update(model, data, v, 0);
}

void ModifySelectionCommand::redo()
{
    update(model, data, v, 1);
}

void ModifySelectionCommand::change(int index, const Selection &value)
{
    auto s = data->entities[index].selection();
    if(s != value)
    {
        v[index] = { s, value };
    }
}
