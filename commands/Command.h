#ifndef COMMAND_H
#define COMMAND_H

#include <QPxEditor/QPxAbstractEditorCommand.h>

class Model;
class ModelData;

class Command : public QPx::AbstractEditorCommand
{
    Q_OBJECT

public:
    Command(const QString &name, Model *model);

protected:
    friend class Model;

    Model *model;
    ModelData *data;
};

#endif // COMMAND_H
