#ifndef SIDEVIEWCONTAINER_H
#define SIDEVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class Relay;

class SideViewContainer : public GuiContainer
{
    Q_OBJECT

public:
    SideViewContainer(Relay *relay, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private:
    Relay *relay;
};

#endif // SIDEVIEWCONTAINER_H
