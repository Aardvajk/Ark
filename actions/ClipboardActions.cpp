#include "ClipboardActions.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "commands/CompositeCommand.h"
#include "commands/ModifySelectionCommand.h"
#include "commands/CreateEntityCommand.h"
#include "commands/DeleteEntityCommand.h"
#include "commands/CopyEntitiesCommand.h"

#include <QPxCore/QPxAction.h>

#include <QtCore/QMimeData>
#include <QtCore/QDataStream>

#include <QtGui/QIcon>
#include <QtGui/QKeySequence>
#include <QtGui/QClipboard>

#include <QtWidgets/QApplication>

#include <pcx/scoped_ptr.h>

ClipboardActions::ClipboardActions(Model *model, ActionList *actions, QObject *parent) : QObject(parent), model(model), actions(actions)
{
    actions->add("Clipboard.Cut", "Cu&t", QKeySequence("Ctrl+X"), QIcon(":/resources/images/cut.png"), QPx::ActionList::Enable::Off);
    actions->add("Clipboard.Copy", "&Copy", QKeySequence("Ctrl+C"), QIcon(":/resources/images/copy.png"), QPx::ActionList::Enable::Off);
    actions->add("Clipboard.Paste", "&Paste", QKeySequence("Ctrl+V"), QIcon(":/resources/images/paste.png"), QPx::ActionList::Enable::Off);

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), SLOT(clipboardChanged()));

    connect(actions->find("Clipboard.Cut"), SIGNAL(triggered()), SLOT(cut()));
    connect(actions->find("Clipboard.Copy"), SIGNAL(triggered()), SLOT(copy()));
    connect(actions->find("Clipboard.Paste"), SIGNAL(triggered()), SLOT(paste()));

    clipboardChanged();
}

void ClipboardActions::modelChanged()
{
    bool any = !model->objects().isEmpty();

    actions->find("Clipboard.Cut")->setEnabled(any);
    actions->find("Clipboard.Copy")->setEnabled(any);
}

void ClipboardActions::clipboardChanged()
{
    auto data = QApplication::clipboard()->mimeData();
    actions->find("Clipboard.Paste")->setEnabled(data && data->hasFormat("aardvajk/ark/entities"));
}

void ClipboardActions::cut()
{
    auto composite = new CompositeCommand("Cut", model);

    auto copy = new CopyEntitiesCommand("", model);
    composite->add(copy);

    copy->copy(model->objects());

    auto command = new DeleteEntityCommand("Cut", model);
    composite->add(command);

    for(auto i: model->objects())
    {
        command->remove(i);
    }

    model->endCommand(composite);
}

void ClipboardActions::copy()
{
    auto command = pcx::to_scoped_ptr(new CopyEntitiesCommand("Copy", model));

    command->copy(model->objects());
    command->redo();
}

void ClipboardActions::paste()
{
    auto data = QApplication::clipboard()->mimeData();
    if(data && data->hasFormat("aardvajk/ark/entities"))
    {
        auto bytes = data->data("aardvajk/ark/entities");
        QDataStream ds(&bytes, QIODevice::ReadOnly);

        auto composite = new CompositeCommand("Paste", model);

        auto select = new ModifySelectionCommand("", model);
        composite->add(select);

        for(auto i: model->selected())
        {
            select->change(i, Selection());
        }

        auto create = new CreateEntityCommand("", model);
        composite->add(create);

        int n;
        ds >> n;

        for(int i = 0; i < n; ++i)
        {
            Entity e;
            ds >> e;

            e.setSelection(Selection::fromElements(Element::Type::Face, e.mesh().faces.count()));

            create->create(e);
        }

        model->endCommand(composite);
    }
}
