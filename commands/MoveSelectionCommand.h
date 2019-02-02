#ifndef MOVESELECTIONCOMMAND_H
#define MOVESELECTIONCOMMAND_H

#include "commands/Command.h"

#include <QPxCore/QPxIndexedPair.h>

#include <GxMaths/GxVector.h>

#include <QtCore/QHash>
#include <QtCore/QSet>

class MoveSelectionCommand : public Command
{
    Q_OBJECT

public:
    MoveSelectionCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void begin(const QHash<int, QSet<int> > &vertices);
    void move(const Gx::Vec3 &value);

private:
    QHash<int, QHash<int, QPx::IndexedPair<Gx::Vec3> > > v;
};

#endif // MOVESELECTIONCOMMAND_H
