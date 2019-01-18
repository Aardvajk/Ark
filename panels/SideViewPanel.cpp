#include "SideViewPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiComboBox.h"

#include "views/PropertyView.h"
#include "views/ToolOptionsView.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QMenu>

SideViewPanel::SideViewPanel(Relay *relay, PropertyModel *properties, QWidget *parent) : GuiPanel(parent), relay(relay), properties(properties)
{
    auto combo = toolBar()->addTypedWidget(new GuiComboBox());
    combo->addItem("Properties");
    combo->addItem("Tools");

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split", this, SLOT(splitVertical()));
    menu->addSeparator();
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = toolBar()->addTypedWidget(new GuiSmallButton(QPixmap(":/resources/images/splitvert.png")));
    button->setMenu(menu);

    auto stack = layout()->addTypedLayout(new QPx::StackedLayout());

    stack->addWidget(new PropertyView(properties));
    stack->addWidget(new ToolOptionsView(relay));

    connect(combo, SIGNAL(currentIndexChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

void SideViewPanel::saveState(QPx::Settings &settings) const
{
}

void SideViewPanel::restoreState(const QPx::Settings &settings)
{
}

SideViewPanel *SideViewPanel::clone() const
{
    return new SideViewPanel(relay, properties);
}
