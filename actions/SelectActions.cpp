#include "SelectActions.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "commands/ModifySelectionCommand.h"

#include <QPxCore/QPxAction.h>
#include <QPxCore/QPxSettings.h>

#include <QtGui/QIcon>
#include <QtGui/QKeySequence>

#include <pcx/indexed_range.h>

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

SelectActions::SelectActions(Model *model, ActionList *actions, QPx::Settings &settings, QObject *parent) : QObject(parent), model(model), actions(actions), settings(settings)
{
    actions->add("Select.All", "&All", QKeySequence("Ctrl+A"), QPx::ActionList::Enable::Off);
    actions->add("Select.None", "&None", QKeySequence("Ctrl+D"), QPx::ActionList::Enable::Off);

    actions->add("Select.Prev.Face", "&Previous Face", QKeySequence("Ctrl+Shift+F"), QPx::ActionList::Enable::Off);
    actions->add("Select.Next.Face", "&Next Face", QKeySequence("Ctrl+F"), QPx::ActionList::Enable::Off);

    actions->add("Select.Whole.Object", "&Whole Object", QKeySequence("Ctrl+G"), QPx::ActionList::Enable::Off);

    connect(model, SIGNAL(changed()), SLOT(modelChanged()));

    connect(actions->find("Select.All"), SIGNAL(triggered()), SLOT(all()));
    connect(actions->find("Select.None"), SIGNAL(triggered()), SLOT(none()));

    connect(actions->find("Select.Prev.Face"), SIGNAL(triggered()), SLOT(prevFace()));
    connect(actions->find("Select.Next.Face"), SIGNAL(triggered()), SLOT(nextFace()));

    connect(actions->find("Select.Whole.Object"), SIGNAL(triggered()), SLOT(wholeObject()));
}

void SelectActions::modelChanged()
{
    bool any = !model->selected().isEmpty();

    actions->find("Select.All")->setEnabled(!model->entities().isEmpty());
    actions->find("Select.None")->setEnabled(any);

    actions->find("Select.Prev.Face")->setEnabled(any);
    actions->find("Select.Next.Face")->setEnabled(any);

    actions->find("Select.Whole.Object")->setEnabled(any && model->objects().count() != model->selected().count());
}

void SelectActions::all()
{
    auto command = new ModifySelectionCommand("Select All", model);

    for(auto i: pcx::indexed_range(model->entities()))
    {
        if(settings["Select"]["Element.Type"].value<Element::Type>() == Element::Type::Vertex)
        {
            command->change(i.index, i.value.selection().merge(Selection::fromElements(Element::Type::Vertex, i.value.mesh().vertices.count())));
        }
        else
        {
            command->change(i.index, i.value.selection().merge(Selection::fromElements(Element::Type::Face, i.value.mesh().faces.count())));
        }
    }

    model->endCommand(command);
}

void SelectActions::none()
{
    auto command = new ModifySelectionCommand("Select None", model);

    for(auto i: model->selected())
    {
        command->change(i, Selection());
    }

    model->endCommand(command);
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
