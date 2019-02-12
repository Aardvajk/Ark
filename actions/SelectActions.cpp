#include "SelectActions.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "commands/ModifySelectionCommand.h"

#include <QPxCore/QPxAction.h>

#include <QtGui/QIcon>
#include <QtGui/QKeySequence>

namespace
{

struct Inc
{
    int operator()(int index, const Mesh &mesh){ return index < mesh.faces.count() - 1 ? index + 1 : 0; }
};

struct Dec
{
    int operator()(int index, const Mesh &mesh){ return index > 0 ? index - 1 : mesh.faces.count() - 1; }
};

template<typename T> void changeFace(const QString &name, Model *model)
{
    auto command = new ModifySelectionCommand(name, model);

    for(auto i: model->selected())
    {
        auto &e = model->entities()[i];
        auto &m = e.mesh();
        auto &s = e.selection();

        Selection ns;

        for(int f = 0; f < m.faces.count(); ++f)
        {
            if(s.elements[Element::Type::Face].contains(f))
            {
                ns = Selection({ T()(f, m) }, { });
            }
        }

        command->change(i, ns);
    }

    model->endCommand(command);
}

}

SelectActions::SelectActions(Model *model, ActionList *actions, QObject *parent) : QObject(parent), model(model), actions(actions)
{
    actions->add("Select.Prev.Face", "&Previous Face", QKeySequence("Ctrl+Shift+F"), QPx::ActionList::Enable::Off);
    actions->add("Select.Next.Face", "&Next Face", QKeySequence("Ctrl+F"), QPx::ActionList::Enable::Off);

    actions->add("Select.Whole.Object", "&Whole Object", QKeySequence("Ctrl+G"), QPx::ActionList::Enable::Off);

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));

    connect(actions->find("Select.Prev.Face"), SIGNAL(triggered()), SLOT(prevFace()));
    connect(actions->find("Select.Next.Face"), SIGNAL(triggered()), SLOT(nextFace()));

    connect(actions->find("Select.Whole.Object"), SIGNAL(triggered()), SLOT(wholeObject()));
}

void SelectActions::modelChanged()
{
    bool any = !model->selected().isEmpty();

    actions->find("Select.Prev.Face")->setEnabled(any);
    actions->find("Select.Next.Face")->setEnabled(any);

    actions->find("Select.Whole.Object")->setEnabled(any && model->objects().count() != model->selected().count());
}

void SelectActions::prevFace()
{
    changeFace<Dec>("Select Previous Face", model);
}

void SelectActions::nextFace()
{
    changeFace<Inc>("Select Next Face", model);
}

void SelectActions::wholeObject()
{
    auto command = new ModifySelectionCommand("Select Whole Object", model);

    for(auto i: model->selected())
    {
        auto &e = model->entities()[i];
        auto &m = e.mesh();

        Selection ns;

        if(e.selection().any())
        {
            ns = Selection::fromElements(Element::Type::Face, m.faces.count());
            command->change(i, ns);
        }
    }

    model->endCommand(command);
}
