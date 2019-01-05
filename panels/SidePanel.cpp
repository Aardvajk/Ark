#include "SidePanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiComboBox.h"

#include <QtWidgets/QLayout>

SidePanel::SidePanel(QWidget *parent) : GuiPanel(parent)
{
    auto cb = toolBar()->addTypedWidget(new GuiComboBox());
    cb->addItem("One");
    cb->addItem("Two");
    cb->addItem("Three");

    addSplitButton(GuiPanel::SplitType::Vertical);

    auto w = new QWidget();
    w->setMinimumWidth(200);

    layout()->addWidget(w);
}

void SidePanel::saveState(QPx::Settings &settings) const
{
}

void SidePanel::restoreState(const QPx::Settings &settings)
{
}

SidePanel *SidePanel::clone() const
{
    return new SidePanel();
}
