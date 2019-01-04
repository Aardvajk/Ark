#include "PropertyPanelContainer.h"

#include "panels/PropertyPanel.h"

#include <QtWidgets/QLayout>

PropertyPanelContainer::PropertyPanelContainer(QWidget *parent)
{
    layout()->addWidget(createPanel());
}

GuiPanel *PropertyPanelContainer::createPanel() const
{
    return new PropertyPanel();
}
