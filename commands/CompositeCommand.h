#ifndef COMPOSITECOMMAND_H
#define COMPOSITECOMMAND_H

#include "commands/Command.h"

#include <vector>

class CompositeCommand : public Command
{
    Q_OBJECT

public:
    CompositeCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void add(Command *command);

private:
    std::vector<Command*> v;
};

#endif // COMPOSITECOMMAND_H
