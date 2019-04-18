#ifndef MODIFYMESHCOMMAND_H
#define MODIFYMESHCOMMAND_H

#include "core/Mesh.h"

#include "commands/Command.h"

#include <QtCore/QHash>

class ModifyMeshCommand : public Command
{
    Q_OBJECT

public:
    ModifyMeshCommand(const QString &name, Model *model);

    virtual bool isValid() const override;
    virtual bool modifiesPersistentState() const override;

    virtual void undo() override;
    virtual void redo() override;

    void modify(int index, const Mesh &mesh);

private:
    QHash<int, QPair<Mesh, Mesh> > v;
};

#endif // MODIFYMESHCOMMAND_H
