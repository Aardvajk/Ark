#include "ModelViewContainer.h"

#include "panels/ModelViewPanel.h"

#include <QtWidgets/QLayout>

ModelViewContainer::ModelViewContainer(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent) : GuiContainer(parent), model(model), graphics(graphics), relay(relay)
{
    layout()->addWidget(createPanel());
}

GuiPanel *ModelViewContainer::createPanel() const
{
    return new ModelViewPanel(model, graphics, relay);
}
