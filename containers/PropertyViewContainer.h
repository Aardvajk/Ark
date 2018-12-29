#ifndef PROPERTYVIEWCONTAINER_H
#define PROPERTYVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class PropertyViewContainer : public GuiContainer
{
public:
    explicit PropertyViewContainer(QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;
};

#endif // PROPERTYVIEWCONTAINER_H
