#include "CreateTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "maths/Grid.h"

#include "views/modelview/ModelView.h"

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

Mesh mesh(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, float grid)
{
    auto a = start;
    auto b = pos;

    if(a.x > b.x) qSwap(a.x, b.x);
    if(a.y > b.y) qSwap(a.y, b.y);
    if(a.z > b.z) qSwap(a.z, b.z);

    auto ag = snapToGridCorner(a, grid);
    auto bg = snapToGridCorner(b, grid);

    int x = 0, y = 1, z = 2;

    switch(projection)
    {
        case Projection::Type::Top:
        case Projection::Type::Bottom: x = 2; y = 0; z = 1; break;

        case Projection::Type::Left:
        case Projection::Type::Right: x = 2; z = 0; break;

        default: break;
    }

    if(a[x] < 0) ag[x] -= grid;
    if(b[x] > 0) bg[x] += grid;

    if(a[y] < 0) ag[y] -= grid;
    if(b[y] < 0) bg[y] -= grid;

    bg[y] += grid;

    ag[z] = -1;
    bg[z] = 1;

    return Mesh::cuboidFromCorners(ag, bg);
}

}

CreateTool::CreateTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model), command(nullptr)
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

        auto m = mesh(view->state().projection, start, start, model->property("Grid").value<float>());

        auto e = EntityFactory::create(Entity::Type::Geometry);
        randomise(e, m);

        e.setMesh(m);
        e.setSelection(Selection::fromElements(Element::Type::Vertex, m.vertices.count()));

        command = new CreateEntityCommand("Create", e, model);
    }
}

void CreateTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    if(command)
    {
        auto p = view->renderParams();
        auto pos = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

        auto e = command->entity();
        e.setMesh(mesh(view->state().projection, start, pos, model->property("Grid").value<float>()));

        command->update(e);
    }
}

void CreateTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(command)
    {
        model->endCommand(command);
        command = nullptr;
    }
}

void CreateTool::focusLost()
{
    if(command)
    {
        command->undo();

        delete command;
        command = nullptr;
    }
}
