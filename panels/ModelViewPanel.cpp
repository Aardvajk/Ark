#include "ModelViewPanel.h"

#include "core/Relay.h"

#include "views/ModelView.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"

#include "graphics/Graphics.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QMenu>

#include <QPxWidgets/QPxPalette.h>
#include <QPxWidgets/QPxLayouts.h>

ModelViewPanel::ModelViewPanel(Model *model, Graphics *graphics, Relay *relay, QWidget *parent) : GuiPanel(parent), model(model), graphics(graphics), relay(relay)
{
    view = layout()->addTypedWidget(new ModelView(model, graphics));

    toolBar()->addStretch();

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

    connect(graphics, SIGNAL(render()), view, SLOT(update()));

    connect(view, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(render(ModelView*,Graphics*,RenderParams)), relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)));
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
