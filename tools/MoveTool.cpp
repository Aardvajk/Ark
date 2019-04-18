#include "MoveTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "maths/Grid.h"

#include "entity/Entity.h"

#include "views/modelview/ModelView.h"

#include "commands/MoveSelectionCommand.h"
#include "commands/ModifyMeshCommand.h"

#include "gui/GuiTextButton.h"

#include <QPxCore/QPxAction.h>

#include <QPxWidgets/QPxLayouts.h>

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

void MoveTool::addOptions(QPx::VBoxLayout *layout) const
{
    connect(layout->addTypedWidget(new GuiTextButton("Rotate")), SIGNAL(clicked()), SLOT(rotate()));
    addGridSnapCheckbox(layout);
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
        auto grid = gridValue(model);

        if(grid.isValid())
        {
            value = Grid::snap(value, grid.value<float>());
        }

        command->move(value);
    }
}

void MoveTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(command)
    {
        model->endCommand(command);
        command = nullptr;
    }
}

void MoveTool::focusLost()
{
    if(command)
    {
        command->undo();

        delete command;
        command = nullptr;
    }
}

void MoveTool::rotate()
{
    if(!model->objects().isEmpty())
    {
        auto command = new ModifyMeshCommand("Rotate", model);

        for(auto i: model->objects())
        {
            auto mesh = model->entities()[i].mesh();

            if(!mesh.vertices.isEmpty())
            {
                Gx::Vec3 av(0, 0, 0);
                for(int i = 0; i < mesh.vertices.count(); ++i)
                {
                    av += mesh.vertices[i];;
                }

                av /= static_cast<float>(mesh.vertices.count());

                auto m = Gx::Matrix::rotationY(M_PI / 2);

                for(auto &v: mesh.vertices)
                {
                    v = av + Gx::Vec3(v - av).transformedCoord(m);

                    auto grid = gridValue(model);
                    if(grid.isValid())
                    {
                        v = Grid::snap(v, grid.value<float>());
                    }
                }

                command->modify(i, mesh);
            }
        }

        model->endCommand(command);
    }
}

