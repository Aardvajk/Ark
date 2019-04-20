#include "CreateTool.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include "graphics/RenderPrimitives.h"

#include "maths/Grid.h"

#include "views/modelview/ModelView.h"

#include "commands/CompositeCommand.h"
#include "commands/ModifySelectionCommand.h"
#include "commands/CreateEntityCommand.h"

#include "controls/SettingsCreateTree.h"

#include "entity/EntityFactory.h"

#include <GxMaths/GxRay.h>

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QIcon>
#include <QtGui/QMouseEvent>

CreateTool::CreateTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent), model(model), type(CreateMesh::Type::Invalid)
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

void CreateTool::addOptions(QPx::VBoxLayout *layout) const
{
    layout->addWidget(new SettingsCreateTree(model, settings["Create"]["Type"]));
    addGridSnapCheckbox(layout);
}

void CreateTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(view->state().projection != Projection::Type::Perspective && event->button() == Qt::LeftButton)
    {
        type = CreateMesh::fromString(settings["Create"]["Type"].value<QString>());

        if(type != CreateMesh::Type::Invalid)
        {
            auto p = view->renderParams();

            start = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;
            mesh = CreateMesh::create(type, view->state().projection, start, start, gridValue(model), model->property("Cursor").value<Gx::Vec3>());
        }
    }
}

void CreateTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    if(type != CreateMesh::Type::Invalid)
    {
        auto p = view->renderParams();
        auto pos = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;

        mesh = CreateMesh::create(type, view->state().projection, start, pos, gridValue(model), model->property("Cursor").value<Gx::Vec3>());
    }
}

void CreateTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(type != CreateMesh::Type::Invalid && event->button() == Qt::LeftButton)
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

        e.setMesh(mesh);
        e.computeTexCoords();

        e.setSelection(Selection::fromElements(Element::Type::Face, mesh.faces.count()));

        auto create = new CreateEntityCommand("", model);
        create->create(e);

        composite->add(create);
        model->endCommand(composite);

        type = CreateMesh::Type::Invalid;
    }
}

void CreateTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(type != CreateMesh::Type::Invalid)
    {
        auto p = view->renderParams();
        RenderPrimitives::wireframeMesh(graphics, p, { }, mesh, Gx::Color(1, 1, 1));
    }
}

void CreateTool::focusLost()
{
    type = CreateMesh::Type::Invalid;
}
