#include "SelectTool.h"

#include "actions/ActionList.h"

#include "graphics/RenderParams.h"
#include "graphics/RenderPrimitives.h"

#include "models/Model.h"

#include "views/ModelView.h"

#include "entity/Entity.h"

#include "core/Selection.h"

#include "controls/SettingsElementBox.h"
#include "controls/SettingsCheckBox.h"

#include "commands/ModifySelectionCommand.h"

#include "physics/Intersect.h"

#include <GxMaths/GxRay.h>

#include <QPxCore/QPxSettings.h>

#include <QPxActions/QPxAction.h>

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

#include <pcx/indexed_range.h>

namespace
{

Selection combine(const Selection &old, const Selection &value, Qt::KeyboardModifiers modifiers)
{
    return modifiers & Qt::ControlModifier ? old.remove(value) : (modifiers & Qt::ShiftModifier ? old.merge(value) : value);
}

void updateSelection(Model *model, QMouseEvent *event, ModifySelectionCommand *command, int index, const Selection &selection)
{
    auto old = model->entities()[index].selection();
    auto combined = combine(old, selection, event->modifiers());

    command->change(index, combined);
}

void selectRay(Model *model, QMouseEvent *event, ModifySelectionCommand *command, const QPx::Settings &settings, const Gx::SizeF &size, const Gx::Matrix &view, const Gx::Matrix &proj)
{
    auto ray = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), size, view, proj);

    QMap<std::size_t, Selection> selections;
    float min = std::numeric_limits<float>::max();;

    for(auto i: pcx::indexed_range(model->entities()))
    {
        float dist = std::numeric_limits<float>::max();
        auto selection = rayIntersect(settings["Element.Type"].value<Element::Type>(), i.value, ray, dist, settings["Visible.Only"].value<bool>());

        if(selection.any())
        {
            int compare = qFuzzyCompare(dist, min) ? 0 : (dist < min ? -1 : 1);
            if(compare <= 0)
            {
                if(compare < 0)
                {
                    selections.clear();
                }

                selections[i.index] = selection;
                min = dist;
            }
        }
    }

    for(auto i: pcx::indexed_range(model->entities()))
    {
        updateSelection(model, event, command, i.index, selections.value(i.index));
    }
}

void selectMarquee(Model *model, QMouseEvent *event, ModifySelectionCommand *command, const QPx::Settings &settings, const QRectF &clip, const Gx::Matrix &transform)
{
    for(auto i: pcx::indexed_range(model->entities()))
    {
        updateSelection(model, event, command, i.index, rectIntersect(settings["Element.Type"].value<Element::Type>(), i.value, clip, transform, settings["Visible.Only"].value<bool>()));
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

QIcon SelectTool::icon() const
{
    return QIcon(":/resources/images/ark.png");
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
        auto p = view->renderParams();

        auto command = new ModifySelectionCommand("Select", model);
        mq.valid(view) ? selectMarquee(model, event, command, settings, mq.clipRect(p.size), p.view * p.proj) : selectRay(model, event, command, settings, p.size, p.view, p.proj);

        model->endCommand(command);

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
