#include "SideViewContainer.h"

#include "panels/SideViewPanel.h"

#include <QtWidgets/QLayout>

SideViewContainer::SideViewContainer(Relay *relay, QWidget *parent) : GuiContainer(parent), relay(relay)
{
    layout()->addWidget(createPanel());
}

GuiPanel *SideViewContainer::createPanel() const
{
    return new SideViewPanel(relay);
}
