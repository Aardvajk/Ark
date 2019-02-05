#ifndef CREATEENTITYCOMMAND_H
#define CREATEENTITYCOMMAND_H

#include "commands/Command.h"

#include "entity/Entity.h"

#include <pcx/optional.h>

class CreateEntityCommand : public Command
{
    Q_OBJECT

public:
    CreateEntityCommand(const QString &name, const Entity &entity, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

private:
    pcx::optional<Entity> v;
};

#endif // CREATEENTITYCOMMAND_H
