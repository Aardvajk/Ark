#ifndef SIDEVIEWCONTAINER_H
#define SIDEVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class Relay;
class PropertyModel;

class SideViewContainer : public GuiContainer
{
    Q_OBJECT

public:
    SideViewContainer(Relay *relay, PropertyModel *properties, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private:
    Relay *relay;
    PropertyModel *properties;
};

#endif // SIDEVIEWCONTAINER_H
