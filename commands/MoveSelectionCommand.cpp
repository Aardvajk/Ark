#include "MoveSelectionCommand.h"

#include "models/Model.h"
#include "models/ModelData.h"

namespace
{

void update(Model *model, ModelData *data, const QHash<int, QHash<int, QPx::IndexedPair<Gx::Vec3> > > &v, int index)
{
    for(auto i = v.begin(); i != v.end(); ++i)
    {
        for(auto j = i.value().begin(); j != i.value().end(); ++j)
        {
            auto &element = v[i.key()][j.key()];
            data->entities[i.key()].mesh().vertices[j.key()] = element[index];
        }
    }

    model->change();
}

}

MoveSelectionCommand::MoveSelectionCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool MoveSelectionCommand::isValid() const
{
    return !v.isEmpty();
}

bool MoveSelectionCommand::modifiesPersistentState() const
{
    return true;
}

void MoveSelectionCommand::undo()
{
    update(model, data, v, 0);
}

void MoveSelectionCommand::redo()
{
    update(model, data, v, 1);
}

void MoveSelectionCommand::begin(const QHash<int, QSet<int> > &vertices)
{
    for(auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        auto &m = data->entities[i.key()].mesh();

        for(auto j: i.value())
        {
            v[i.key()][j] = { m.vertices[j], m.vertices[j] };
        }
    }
}

void MoveSelectionCommand::move(const Gx::Vec3 &value)
{
    for(auto i = v.begin(); i != v.end(); ++i)
    {
        for(auto j = i.value().begin(); j != i.value().end(); ++j)
        {
            auto &element = v[i.key()][j.key()];

            element.second = element.first + value;
            data->entities[i.key()].mesh().vertices[j.key()] = element.second;
        }
    }

    model->change();
}

