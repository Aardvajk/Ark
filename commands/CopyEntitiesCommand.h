#ifndef COPYENTITIESCOMMAND_H
#define COPYENTITIESCOMMAND_H

#include "commands/Command.h"

class CopyEntitiesCommand : public Command
{
    Q_OBJECT

public:
    CopyEntitiesCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void copy(const QVector<int> &indices);

private:
    QVector<int> v;
};

#endif // COPYENTITIESCOMMAND_H
