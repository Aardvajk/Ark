#include "SidePanelContainer.h"

#include "panels/SidePanel.h"

#include <QtWidgets/QLayout>

SidePanelContainer::SidePanelContainer(QWidget *parent)
{
    layout()->addWidget(createPanel());
}

GuiPanel *SidePanelContainer::createPanel() const
{
    return new SidePanel();
}
