#ifndef SIDEVIEWPANEL_H
#define SIDEVIEWPANEL_H

#include "gui/GuiPanel.h"

namespace QPx
{

class VBoxLayout;

}

class Model;
class Relay;
class PropertyTypeFactory;
class Tool;

class SideViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    SideViewPanel(Model *model, Relay *relay, PropertyTypeFactory *factory, Tool *tool, QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual SideViewPanel *clone() const override;

private slots:
    void toolSelected(Tool *tool);
    void comboIndexChanged(int index);

private:
    Model *model;
    Relay *relay;
    PropertyTypeFactory *factory;
    Tool *currentTool;
    QPx::VBoxLayout *panelLayout;
};

#endif // SIDEVIEWPANEL_H
