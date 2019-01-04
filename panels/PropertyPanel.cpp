#include "PropertyPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiComboBox.h"

#include <QtWidgets/QLayout>

PropertyPanel::PropertyPanel(QWidget *parent) : GuiPanel(parent)
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

void PropertyPanel::saveState(QPx::Settings &settings) const
{
}

void PropertyPanel::restoreState(const QPx::Settings &settings)
{
}

PropertyPanel *PropertyPanel::clone() const
{
    return new PropertyPanel();
}
