#include "SelectTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "entity/Entity.h"
#include "entity/EntityIntersect.h"

#include "graphics/RenderParams.h"
#include "graphics/RenderPrimitives.h"

#include "views/ModelView.h"

#include "commands/ModifyCommand.h"

#include <GxMaths/GxColor.h>
#include <GxMaths/GxRay.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

namespace
{

QKeySequence shortcut(Selection::Type type)
{
    switch(type)
    {
        case Selection::Type::Object: return QKeySequence("1");
        case Selection::Type::Face: return QKeySequence("2");
        case Selection::Type::Vertex: return QKeySequence("3");

        default: return QKeySequence();
    }
}

void updateSelection(Model *model, QMouseEvent *event, ModifyCommand *command, int index, const Selection &sel)
{
    auto old = model->entities()[index].properties()["Selection"].toSelection();

    if(event->modifiers() & Qt::ControlModifier)
    {
        command->change(Selection::Type::Object, "Selection", index, -1, QVariant::fromValue(old.remove(sel)));
    }
    else
    {
        command->change(Selection::Type::Object, "Selection", index, -1, QVariant::fromValue(event->modifiers() & Qt::ShiftModifier ? old.merge(sel) : sel));
    }
}

void selectRay(Selection::Type type, Model *model, ModelView *view, QMouseEvent *event, ModifyCommand *command)
{
    auto p = view->renderParams();
    auto ray = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj);

    QMap<int, Selection> selections;
    float min = std::numeric_limits<float>::max();;

    for(int i = 0; i < model->entities().count(); ++i)
    {
        float dist = std::numeric_limits<float>::max();
        auto sel = rayIntersect(type, model->entities()[i], ray, dist);

        if(sel.any())
        {
            int compare = qFuzzyCompare(dist, min) ? 0 : (dist < min ? -1 : 1);
            if(compare <= 0)
            {
                if(compare < 0)
                {
                    selections.clear();
                }

                selections[i] = sel;
                min = dist;
            }
        }
    }

    for(int i = 0; i < model->entities().count(); ++i)
    {
        updateSelection(model, event, command, i, selections.value(i));
    }
}

void selectMarquee(Selection::Type type, Model *model, ModelView *view, QMouseEvent *event, const Marquee &mq, ModifyCommand *command)
{
    auto p = view->renderParams();

    auto clip = mq.clipRect(p.size);
    auto tr = p.view * p.proj;

    for(int i = 0; i < model->entities().count(); ++i)
    {
        updateSelection(model, event, command, i, rectIntersect(type, model->entities()[i], clip, tr));
    }
}

}

SelectTool::SelectTool(Model *model, ActionList *actions, Selection::Type type, QObject *parent) : Tool(parent), model(model), type(type)
{
    connect(actions->add(QString("Tools.Select.%1").arg(name()), name(), shortcut(type), QIcon()), SIGNAL(triggered()), SIGNAL(select()));
}

QString SelectTool::name() const
{
    return Selection::typeToString(type);
}

QPixmap SelectTool::icon() const
{
    return QPixmap(":/resources/images/ark.png");
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
    if(mq.widget())
    {
        mq.update(event);
    }
}

void SelectTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(mq.widget())
    {
        auto command = new ModifyCommand("Select", model);
        mq.valid() ? selectMarquee(type, model, view, event, mq, command) : selectRay(type, model, view, event, command);

        model->endCommand(command);

        mq.end();
    }
}

void SelectTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mq.widget() == view)
    {
        RenderPrimitives::invertBox(graphics, params, mq.anchor(), mq.position());
    }
}

void SelectTool::focusLost()
{
    mq.end();
}
