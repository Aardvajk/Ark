#include "PropertyPanel.h"

#include <QtWidgets/QLayout>

PropertyPanel::PropertyPanel(QWidget *parent) : GuiPanel(parent)
{
    layout()->addWidget(new QWidget());
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
