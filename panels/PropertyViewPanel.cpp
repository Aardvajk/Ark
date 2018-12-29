#include "PropertyViewPanel.h"

#include "views/PropertyView.h"

#include <QtWidgets/QLayout>

PropertyViewPanel::PropertyViewPanel(QWidget *parent) : GuiPanel(parent)
{
    layout()->addWidget(new PropertyView());
}

void PropertyViewPanel::saveState(QPx::Settings &settings) const
{
}

void PropertyViewPanel::restoreState(const QPx::Settings &settings)
{
}

PropertyViewPanel *PropertyViewPanel::clone() const
{
    return new PropertyViewPanel();
}
