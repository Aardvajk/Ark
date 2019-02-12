#ifndef CREATEENTITYCOMMAND_H
#define CREATEENTITYCOMMAND_H

#include "commands/Command.h"

#include "entity/Entity.h"

#include <QVector>

class CreateEntityCommand : public Command
{
    Q_OBJECT

public:
    CreateEntityCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void create(const Entity &entity);

private:
    QVector<Entity> v;
};

#endif // CREATEENTITYCOMMAND_H
