#include "CreateTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "maths/Grid.h"

#include "graphics/RenderPrimitives.h"

#include "views/modelview/ModelView.h"

#include "commands/CompositeCommand.h"
#include "commands/ModifySelectionCommand.h"
#include "commands/CreateEntityCommand.h"

#include "entity/EntityFactory.h"

#include <GxMaths/GxRay.h>

#include <QtGui/QIcon>
#include <QtGui/QMouseEvent>

namespace
{

void randomise(Entity &e, const Mesh &m)
{
    for(int i = 0; i < m.faces.count(); ++i)
    {
        e.addSubProperty(Element::Type::Face, i, "Color", Property(QColor(std::rand() % 255, std::rand() % 255, std::rand() % 255)));
    }
}

Mesh blockMesh(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const Grid &grid)
{
    auto a = start;
    auto b = pos;

    if(a.x > b.x) qSwap(a.x, b.x);
    if(a.y > b.y) qSwap(a.y, b.y);
    if(a.z > b.z) qSwap(a.z, b.z);

    int x = 0, y = 1, z = 2;

    switch(projection)
    {
        case Projection::Type::Top:
        case Projection::Type::Bottom: x = 2; y = 0; z = 1; break;

        case Projection::Type::Left:
        case Projection::Type::Right: x = 2; z = 0; break;

        default: break;
    }

    if(grid.valid())
    {
        auto g = grid.value();

        auto ag = Grid::snapCorner(a, g);
        auto bg = Grid::snapCorner(b, g);

        if(a[x] < 0) ag[x] -= g;
        if(b[x] > 0) bg[x] += g;

        if(a[y] < 0) ag[y] -= g;
        if(b[y] < 0) bg[y] -= g;

        bg[y] += g;

        a = ag;
        b = bg;
    }

    a[z] = -1;
    b[z] = 1;

    return Mesh::cuboidFromCorners(a, b);
}

}

CreateTool::CreateTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model)
{
    connect(actions->add("Tools.Create", "Create", QKeySequence("3")), SIGNAL(triggered()), SLOT(select()));
}

QString CreateTool::name() const
{
    return "Create";
}

QIcon CreateTool::icon() const
{
    return QIcon(":/resources/images/ark.png");
}

void CreateTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(view->state().projection != Projection::Type::Perspective && event->button() == Qt::LeftButton)
    {
        auto p = view->renderParams();

        start = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;
        mesh = blockMesh(view->state().projection, start, start, model->property("Grid").value<Grid>());
    }
}

void CreateTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    if(mesh)
    {
        auto p = view->renderParams();
        auto pos = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

        mesh = blockMesh(view->state().projection, start, pos, model->property("Grid").value<Grid>());
    }
}

void CreateTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(mesh)
    {
        auto composite = new CompositeCommand("Create", model);

        if(!(event->modifiers() & Qt::ShiftModifier))
        {
            auto command = new ModifySelectionCommand("", model);
            composite->add(command);

            for(auto i: model->selected())
            {
                command->change(i, Selection());
            }
        }

        auto e = EntityFactory::create(Entity::Type::Geometry);

        e.setMesh(*mesh);
        e.setSelection(Selection::fromElements(Element::Type::Face, mesh->faces.count()));

        composite->add(new CreateEntityCommand("", e, model));
        model->endCommand(composite);

        mesh = { };
    }
}

void CreateTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mesh)
    {
        auto p = view->renderParams();
        RenderPrimitives::wireframeMesh(graphics, p, { }, *mesh, Gx::Color(1, 1, 1));
    }
}

void CreateTool::focusLost()
{
    mesh = { };
}
