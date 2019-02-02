#include "MoveTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "views/modelview/ModelView.h"

#include "maths/Grid.h"

#include "commands/MoveSelectionCommand.h"

#include <QPxCore/QPxAction.h>

#include <GxMaths/GxRay.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

MoveTool::MoveTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model), command(nullptr)
{
    connect(actions->add("Tools.Move", "Move", QKeySequence("2")), SIGNAL(triggered()), SLOT(select()));
}

QString MoveTool::name() const
{
    return "Move";
}

QIcon MoveTool::icon() const
{
    return QIcon(":/resources/images/ark.png");
}

void MoveTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(view->state().projection != Projection::Type::Perspective && event->button() == Qt::LeftButton)
    {
        command = new MoveSelectionCommand("Move", model);

        auto p = view->renderParams();
        start = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

        QHash<int, QSet<int> > vs;
        for(auto i: model->selected())
        {
            auto &e = model->entities()[i];
            vs[i] = e.selection().selectedVertices(e.mesh());
        }

        command->begin(vs);
    }
}

void MoveTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    if(command)
    {
        auto p = view->renderParams();
        auto pos = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

        auto value = pos - start;
        auto grid = model->property("Grid");

        if(grid.value<QVariant>().isValid())
        {
            value = snapToGrid(value, grid.value<float>());
        }

        command->move(value);
    }
}

void MoveTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(command)
    {
        model->endCommand(command);

        start = { };
        command = nullptr;
    }
}

void MoveTool::focusLost()
{
    delete command;
    command = nullptr;
}
