#ifndef DELETEENTITYCOMMAND_H
#define DELETEENTITYCOMMAND_H

#include "commands/Command.h"

#include "entity/Entity.h"

#include <QtCore/QMap>

class DeleteEntityCommand : public Command
{
    Q_OBJECT

public:
    DeleteEntityCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void remove(int index);

private:
    QMap<int, Entity> v;
};

#endif // DELETEENTITYCOMMAND_H
