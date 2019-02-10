#include "EditActions.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "commands/DeleteEntityCommand.h"

#include <QPxCore/QPxAction.h>

#include <QtGui/QIcon>
#include <QtGui/QKeySequence>

namespace
{

void updateUndoAction(QPx::Action *action, bool enabled, const QString &name, const QString &text)
{
    action->setEnabled(enabled);
    action->setText(text.isEmpty() ? name : QString("%1 %2").arg(name).arg(text));
}

}

EditActions::EditActions(Model *model, ActionList *actions, QObject *parent) : QObject(parent), model(model), actions(actions)
{
    actions->add("Edit.Undo", "&Undo", QKeySequence("Ctrl+Z"), QIcon(":/resources/images/undo.png"), QPx::ActionList::Enable::Off);
    actions->add("Edit.Redo", "&Redo", QKeySequence("Ctrl+Y"), QIcon(":/resources/images/redo.png"), QPx::ActionList::Enable::Off);

    actions->add("Edit.Delete", "&Delete", QKeySequence("Del"), QPx::ActionList::Enable::Off);

    connect(actions->find("Edit.Undo"), SIGNAL(triggered()), model, SLOT(undo()));
    connect(actions->find("Edit.Redo"), SIGNAL(triggered()), model, SLOT(redo()));

    connect(actions->find("Edit.Delete"), SIGNAL(triggered()), SLOT(del()));

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));
    connect(model, SIGNAL(undoStateChanged()), SLOT(undoStateChanged()));
}

void EditActions::modelChanged()
{
    actions->find("Edit.Delete")->setEnabled(!model->objects().isEmpty());
}

void EditActions::undoStateChanged()
{
    updateUndoAction(actions->find("Edit.Undo"), model->canUndo(), "Undo", model->lastCommandName());
    updateUndoAction(actions->find("Edit.Redo"), model->canRedo(), "Redo", model->nextCommandName());
}

void EditActions::del()
{
    auto command = new DeleteEntityCommand("Delete", model);

    for(auto i: model->objects())
    {
        command->remove(i);
    }

    model->endCommand(command);
}
