#include "SideViewContainer.h"

#include "core/Relay.h"

#include "panels/SideViewPanel.h"

#include <QtWidgets/QLayout>

SideViewContainer::SideViewContainer(Model *model, Relay *relay, PropertyTypeFactory *factory, QWidget *parent) : GuiContainer(parent), model(model), relay(relay), factory(factory), currentTool(nullptr)
{
    layout()->addWidget(createPanel());

    connect(relay, SIGNAL(toolSelected(Tool*)), SLOT(toolSelected(Tool*)));
}

GuiPanel *SideViewContainer::createPanel() const
{
    return new SideViewPanel(model, relay, factory, currentTool);
}

void SideViewContainer::toolSelected(Tool *tool)
{
    currentTool = tool;
}
