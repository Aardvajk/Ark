#include "ModelViewPanel.h"

#include "views/ModelView.h"
#include "views/ModelViewRelay.h"

#include "graphics/Graphics.h"

#include <QtWidgets/QLayout>

ModelViewPanel::ModelViewPanel(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent) : GuiPanel(parent), model(model), graphics(graphics), relay(relay)
{
    view = new ModelView(model, graphics);
    layout()->addWidget(view);

    connect(graphics, SIGNAL(render()), view, SLOT(update()));

    connect(view, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), relay, SLOT(mousePressedSlot(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), relay, SLOT(mouseMovedSlot(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), relay, SLOT(mouseReleasedSlot(ModelView*,QMouseEvent*)));
    connect(view, SIGNAL(render(ModelView*,Graphics*,RenderParams)), relay, SLOT(renderSlot(ModelView*,Graphics*,RenderParams)));
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
