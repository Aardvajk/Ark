#ifndef PROPERTYPANELCONTAINER_H
#define PROPERTYPANELCONTAINER_H

#include "gui/GuiContainer.h"

class PropertyPanelContainer : public GuiContainer
{
public:
    explicit PropertyPanelContainer(QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;
};

#endif // PROPERTYPANELCONTAINER_H
