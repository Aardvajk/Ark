#ifndef MODELVIEWPANELCONTAINER_H
#define MODELVIEWPANELCONTAINER_H

#include "gui/GuiContainer.h"

class Model;
class Graphics;
class ModelViewRelay;

class ModelViewPanelContainer : public GuiContainer
{
public:
    ModelViewPanelContainer(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private:
    Model *model;
    Graphics *graphics;
    ModelViewRelay *relay;
};

#endif // MODELVIEWPANELCONTAINER_H
