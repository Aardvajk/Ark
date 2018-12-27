#include "ModelViewPanel.h"

#include "views/ModelView.h"

#include "graphics/Graphics.h"

#include <QtWidgets/QLayout>

ModelViewPanel::ModelViewPanel(Model *model, Graphics *graphics, QWidget *parent) : Panel(parent), model(model), graphics(graphics)
{
    view = new ModelView(model, graphics);
    layout()->addWidget(view);

    connect(graphics, SIGNAL(render()), view, SLOT(update()));
}

void ModelViewPanel::saveState(QPx::Settings &settings) const
{
}

ModelViewPanel *ModelViewPanel::clone() const
{
    return new ModelViewPanel(model, graphics);
}
