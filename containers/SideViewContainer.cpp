#include "SideViewContainer.h"

#include "panels/SideViewPanel.h"

#include <QtWidgets/QLayout>

SideViewContainer::SideViewContainer(Relay *relay, PropertyModel *properties, QWidget *parent) : GuiContainer(parent), relay(relay), properties(properties)
{
    layout()->addWidget(createPanel());
}

GuiPanel *SideViewContainer::createPanel() const
{
    return new SideViewPanel(relay, properties);
}
