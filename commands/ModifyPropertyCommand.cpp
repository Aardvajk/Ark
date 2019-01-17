#include "ModifyPropertyCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

namespace
{

void update(ModelData *data, const StoredValue &p, const QVariant &value)
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

ModifyPropertyCommand::ModifyPropertyCommand(const QString &name, Model *model) : Command(name, model), persist(false)
{
}

bool ModifyPropertyCommand::isValid() const
{
    return !v.isEmpty();
}

bool ModifyPropertyCommand::modifiesPersistentState() const
{
    return persist;
}

void ModifyPropertyCommand::undo()
{
    for(auto &p: v) update(data, p, p.old);
    model->change();
}

void ModifyPropertyCommand::redo()
{
    for(auto &p: v) update(data, p, p.value);
    model->change();
}

void ModifyPropertyCommand::change(Element::Type type, const QString &id, int index, int subIndex, const QVariant &value)
{
    auto &p = index < 0 ? data->properties[id] : (subIndex < 0 ? data->entities[index].properties()[id] : data->entities[index].subProperties()[type][subIndex][id]);
    if(value != p.value<QVariant>())
    {
        if(!(p.flags() & Property::Flag::NonPersistent)) persist = true;
        v.append(StoredValue(type, id, index, subIndex, p.value<QVariant>(), value));
    }
}
