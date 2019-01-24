#ifndef MODIFYSELECTIONCOMMAND_H
#define MODIFYSELECTIONCOMMAND_H

#include "commands/Command.h"

#include "core/Selection.h"

#include <QPxCore/QPxIndexedPair.h>

#include <QtCore/QHash>

class ModifySelectionCommand : public Command
{
    Q_OBJECT

public:
    ModifySelectionCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void change(int index, const Selection &value);

private:
    QHash<int, QPx::IndexedPair<Selection> > v;
};

#endif // MODIFYSELECTIONCOMMAND_H
