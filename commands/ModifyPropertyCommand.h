#ifndef MODIFYPROPERTYCOMMAND_H
#define MODIFYPROPERTYCOMMAND_H

#include "commands/Command.h"
#include "commands/StoredValue.h"

#include <QtCore/QList>

class ModifyPropertyCommand : public Command
{
    Q_OBJECT

public:
    ModifyPropertyCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void change(Element::Type type, const QString &id, int index, int subIndex, const QVariant &value);

private:
    QList<StoredValue> v;
    bool persist;
};

#endif // MODIFYPROPERTYCOMMAND_H
