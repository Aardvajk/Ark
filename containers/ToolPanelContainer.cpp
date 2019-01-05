#include "ToolPanelContainer.h"

#include "gui/GuiBar.h"
#include "gui/GuiSeparator.h"

#include "panels/ToolPanel.h"

#include <QPxWidgets/QPxLayouts.h>

ToolPanelContainer::ToolPanelContainer(ToolPanel *panel, QWidget *parent) : QWidget(parent)
{
    auto layout = new QPx::VBoxLayout(this);

    layout->addTypedWidget(new GuiBar())->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    layout->addTypedWidget(new GuiSeparator(Qt::Horizontal))->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    layout->addTypedWidget(panel);
}
