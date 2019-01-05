#include "ModelViewPanelContainer.h"

#include "panels/ModelViewPanel.h"

#include <QtWidgets/QLayout>

ModelViewPanelContainer::ModelViewPanelContainer(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent) : GuiContainer(parent), model(model), graphics(graphics), relay(relay)
{
    layout()->addWidget(createPanel());
}

GuiPanel *ModelViewPanelContainer::createPanel() const
{
    return new ModelViewPanel(model, graphics, relay);
}
