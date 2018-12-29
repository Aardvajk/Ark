#include "PropertyViewContainer.h"

#include "panels/PropertyViewPanel.h"

#include <QtWidgets/QLayout>

PropertyViewContainer::PropertyViewContainer(QWidget *parent)
{
    layout()->addWidget(createPanel());
}

GuiPanel *PropertyViewContainer::createPanel() const
{
    return new PropertyViewPanel();
}
