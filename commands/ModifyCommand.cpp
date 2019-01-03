#include "ModifyCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

namespace
{

void update(ModelData *data, const StoredVariant &p, const QVariant &value)
{
    if(p.index < 0)
    {
        data->properties[p.id].setValue(value);
    }
    else if(p.subIndex < 0)
    {
        data->entities[p.index].properties()[p.id].setValue(value);
    }
    else
    {
        data->entities[p.index].subProperties()[p.type][p.subIndex][p.id].setValue(value);
    }
}

}

ModifyCommand::ModifyCommand(const QString &name, Model *model) : Command(name, model), persist(false)
{
}

bool ModifyCommand::isValid() const
{
    return !v.empty();
}

bool ModifyCommand::modifiesPersistentState() const
{
    return persist;
}

void ModifyCommand::undo()
{
    for(auto &p: v) update(data, p, p.old);
    model->change();
}

void ModifyCommand::redo()
{
    for(auto &p: v) update(data, p, p.value);
    model->change();
}

void ModifyCommand::change(Selection::Type type, const QString &id, int index, int subIndex, const QVariant &value)
{
    auto &p = index < 0 ? data->properties[id] : (subIndex < 0 ? data->entities[index].properties()[id] : data->entities[index].subProperties()[type][subIndex][id]);
    if(value != p.value())
    {
        if(!(p.flags() & Property::Flag::NonPersistent)) persist = true;
        v.push_back(StoredVariant(type, id, index, subIndex, p.value(), value));
    }
}
