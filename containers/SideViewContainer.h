#ifndef SIDEVIEWCONTAINER_H
#define SIDEVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class Model;
class Relay;
class PropertyTypeFactory;
class Tool;

class SideViewContainer : public GuiContainer
{
    Q_OBJECT

public:
    SideViewContainer(Model *model, Relay *relay, PropertyTypeFactory *factory, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private slots:
    void toolSelected(Tool *tool);

private:
    Model *model;
    Relay *relay;
    PropertyTypeFactory *factory;
    Tool *currentTool;
};

#endif // SIDEVIEWCONTAINER_H
