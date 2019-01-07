#include "SideViewContainer.h"

#include "panels/SideViewPanel.h"

#include <QtWidgets/QLayout>

SideViewContainer::SideViewContainer(QWidget *parent) : GuiContainer(parent)
{
    layout()->addWidget(createPanel());
}

GuiPanel *SideViewContainer::createPanel() const
{
    return new SideViewPanel();
}
