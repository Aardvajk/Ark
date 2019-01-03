#include "Command.h"

#include "models/Model.h"

Command::Command(const QString &name, Model *model) : QPx::AbstractEditorCommand(name, model), model(model), data(nullptr)
{
    model->beginCommand(this);
}
