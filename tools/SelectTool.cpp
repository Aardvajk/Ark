#include "SelectTool.h"

#include "actions/ActionList.h"

#include "graphics/RenderParams.h"
#include "graphics/RenderPrimitives.h"

#include "models/Model.h"

#include "views/ModelView.h"

#include "entity/Entity.h"

#include "properties/custom/Selection.h"

#include "controls/SettingsElementBox.h"
#include "controls/SettingsCheckBox.h"

#include "commands/ModifyPropertyCommand.h"

#include "physics/Intersect.h"

#include <QPxCore/QPxSettings.h>

#include <QPxActions/QPxAction.h>

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

#include <pcx/indexed_range.h>

namespace
{

void updateSelection(Model *model, QMouseEvent *event, ModifyPropertyCommand *command, int index, const Selection &selection)
{
    auto old = model->entities()[index].properties()["Selection"].value<Selection>();

    if(event->modifiers() & Qt::ControlModifier)
    {
        command->change(Element::Type::Object, "Selection", index, -1, QVariant::fromValue(old.remove(selection)));
    }
    else
    {
        command->change(Element::Type::Object, "Selection", index, -1, QVariant::fromValue(event->modifiers() & Qt::ShiftModifier ? old.merge(selection) : selection));
    }
}

}

SelectTool::SelectTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model)
{
    connect(actions->add("Tools.Select", "Select", QKeySequence("1")), SIGNAL(triggered()), SLOT(select()));
}

QString SelectTool::name() const
{
    return "Select";
}

QPixmap SelectTool::icon() const
{
    return QPixmap(":/resources/images/ark.png");
}

void SelectTool::addOptions(QPx::VBoxLayout *layout) const
{
    layout->addWidget(new SettingsElementBox(settings["Element.Type"]));
    layout->addWidget(new SettingsCheckBox(settings["Visible.Only"], "Visible Only"));
}

void SelectTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mq.begin(view, event);
    }
}

void SelectTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    mq.update(view, event);
}

void SelectTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(mq.active(view) && event->button() == Qt::LeftButton)
    {
        if(mq.valid(view))
        {
            ModifyPropertyCommand *command = new ModifyPropertyCommand("Select", model);

            auto p = view->renderParams();

            auto clip = mq.clipRect(p.size);
            auto tr = p.view * p.proj;

            for(auto i: pcx::indexed_range(model->entities()))
            {
                updateSelection(model, event, command, i.index, rectIntersect(settings["Element.Type"].value<Element::Type>(), i.value, clip, tr, settings["Visible.Only"].value<bool>()));
            }

            model->endCommand(command);
        }

        mq.end(view);
    }
}

void SelectTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mq.active(view))
    {
        RenderPrimitives::invertBox(graphics, params, mq.anchor(), mq.position());
    }
}

void SelectTool::focusLost()
{
    mq.end(mq.widget());
}
