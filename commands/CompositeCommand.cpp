#include "CompositeCommand.h"

#include <pcx/range_reverse.h>

CompositeCommand::CompositeCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool CompositeCommand::isValid() const
{
    for(auto c: v)
    {
        if(c->isValid()) return true;
    }

    return false;
}

bool CompositeCommand::modifiesPersistentState() const
{
    for(auto c: v)
    {
        if(c->modifiesPersistentState()) return true;
    }

    return false;
}

void CompositeCommand::undo()
{
    for(auto c: pcx::range_reverse(v))
    {
        c->undo();
    }
}

void CompositeCommand::redo()
{
    for(auto c: v)
    {
        c->redo();
    }
}

void CompositeCommand::add(Command *command)
{
    v.push_back(command);
}
