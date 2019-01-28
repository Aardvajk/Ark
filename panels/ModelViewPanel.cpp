#include "ModelViewPanel.h"

#include "core/Relay.h"

#include "maths/Projection.h"

#include "views/modelview/PerspectiveModelView.h"
#include "views/modelview/OrthoModelView.h"

#include "gui/GuiBar.h"
#include "gui/GuiComboBox.h"
#include "gui/GuiSmallButton.h"

#include "graphics/Graphics.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QMenu>

#include <QPxWidgets/QPxPalette.h>
#include <QPxWidgets/QPxLayouts.h>

#include <pcx/enum_range.h>

ModelViewPanel::ModelViewPanel(Model *model, Graphics *graphics, Relay *relay, QWidget *parent) : GuiPanel(parent), model(model), graphics(graphics), view(nullptr), relay(relay)
{
    combo = toolBar()->addTypedWidget(new GuiComboBox());
    for(auto p: pcx::enum_range(Projection::Type::Perspective, Projection::Type::None))
    {
        combo->addItem(Projection::toString(p), QVariant::fromValue(p));

        states[p].projection = p;
        states[p].camera = Projection::camera(p);
    }

    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(comboChanged(int)));

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addAction(QIcon(":/resources/images/splitgrid.png"), "Split Grid", this, SLOT(splitGrid()));
    menu->addSeparator();
    menu->addAction(maximizeAction());
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = setPanelButton(toolBar()->addTypedWidget(new GuiSmallButton(QIcon(":/resources/images/splitgrid.png"))));
    button->setMenu(menu);

    combo->setCurrentIndex(5);
}

void ModelViewPanel::saveState(QPx::Settings &settings) const
{
}

void ModelViewPanel::restoreState(const QPx::Settings &settings)
{
}

ModelViewPanel *ModelViewPanel::clone() const
{
    return new ModelViewPanel(model, graphics, relay);
}

void ModelViewPanel::comboChanged(int index)
{
    if(view)
    {
        auto s = view->state();
        states[s.projection] = s;

        delete view;
    }

    auto state = states[combo->itemData(index).value<Projection::Type>()];
    switch(state.projection)
    {
        case Projection::Type::Perspective: view = layout()->addTypedWidget(new PerspectiveModelView(model, graphics, state)); break;

        default: view = layout()->addTypedWidget(new OrthoModelView(model, graphics, state));
    }

    connect(view, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(render(ModelView*,Graphics*,RenderParams)), relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)));

    connect(graphics, SIGNAL(render()), view, SLOT(update()));
}
