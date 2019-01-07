#ifndef MODELVIEWCONTAINER_H
#define MODELVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class Model;
class Graphics;
class Relay;

class ModelViewContainer : public GuiContainer
{
    Q_OBJECT

public:
    ModelViewContainer(Model *model, Graphics *graphics, Relay *relay, QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;

private:
    Model *model;
    Graphics *graphics;
    Relay *relay;
};

#endif // MODELVIEWCONTAINER_H
