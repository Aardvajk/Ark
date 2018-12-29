#ifndef MODELVIEWCONTAINER_H
#define MODELVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class Model;
class Graphics;
class ModelViewRelay;

class ModelViewContainer : public GuiContainer
{
public:
    ModelViewContainer(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private:
    Model *model;
    Graphics *graphics;
    ModelViewRelay *relay;
};

#endif // MODELVIEWCONTAINER_H
