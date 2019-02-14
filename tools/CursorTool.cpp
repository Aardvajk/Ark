#include "CursorTool.h"

#include "actions/ActionList.h"

#include "commands/ModifyPropertyCommand.h"

#include "views/modelview/ModelView.h"

#include "maths/Grid.h"

#include "models/Model.h"

#include "graphics/RenderParams.h"
#include "graphics/RenderPrimitives.h"

#include <GxMaths/GxRay.h>

#include <QPxCore/QPxAction.h>

#include <QtGui/QMouseEvent>

namespace
{

Gx::Vec3 update(ModelView *view, QMouseEvent *event, Model *model, const QVariant &grid)
{
    auto p = view->renderParams();
    auto pos = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

    if(grid.isValid())
    {
        pos = Grid::snap(pos, grid.value<float>());
    }

    return pos;
}

}

CursorTool::CursorTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model), mv(nullptr)
{
    connect(actions->add("Tools.Cursor", "Cursor", QKeySequence("4")), SIGNAL(triggered()), SLOT(select()));
}

QString CursorTool::name() const
{
    return "Cursor";
}

QIcon CursorTool::icon() const
{
    return QIcon(":/resources/images/ark.png");
}

void CursorTool::addOptions(QPx::VBoxLayout *layout) const
{
    addGridSnapCheckbox(layout);
}

void CursorTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && view->state().projection != Projection::Type::Perspective)
    {
        pos = update(view, event, model, gridValue(model));
        mv = view;
    }
}

void CursorTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    if(mv == view)
    {
        pos = update(view, event, model, gridValue(model));
    }
}

void CursorTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(pos && event->button() == Qt::LeftButton)
    {
        auto p = view->renderParams();

        auto command = new ModifyPropertyCommand("Move Cursor", model);
        command->change(Element::Type::None, "Cursor", -1, -1, QVariant::fromValue(Projection::merge(p.projection, model->property("Cursor").value<Gx::Vec3>(), *pos)));

        model->endCommand(command);

        pos = { };
        mv = nullptr;
    }
}

void CursorTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mv == view)
    {
        RenderPrimitives::cursor(graphics, params, RenderState::Flag::NoZ | RenderState::Flag::NoZWrite, *pos, Gx::Color(0.8f, 0.8f, 0.8f));
    }
}

void CursorTool::focusLost()
{
    pos = { };
    mv = nullptr;
}
