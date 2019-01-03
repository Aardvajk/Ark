#ifndef MODIFYCOMMAND_H
#define MODIFYCOMMAND_H

#include "commands/Command.h"
#include "commands/StoredVariant.h"

#include <vector>

class ModifyCommand : public Command
{
    Q_OBJECT

public:
    ModifyCommand(const QString &name, Model *model);

    bool isValid() const override;
    bool modifiesPersistentState() const override;

    void undo() override;
    void redo() override;

    void change(Selection::Type type, const QString &id, int index, int subIndex, const QVariant &value);

private:
    std::vector<StoredVariant> v;
    bool persist;
};

#endif // MODIFYCOMMAND_H
