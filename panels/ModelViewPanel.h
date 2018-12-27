#ifndef MODELVIEWPANEL_H
#define MODELVIEWPANEL_H

#include "gui/GuiPanel.h"

class Model;
class Graphics;
class ModelView;
class ModelViewRelay;

class ModelViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    ModelViewPanel(Model *model, Graphics *graphics, ModelViewRelay *relay, QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;

protected:
    virtual ModelViewPanel *clone() const override;

private:
    Model *model;
    Graphics *graphics;
    ModelView *view;
    ModelViewRelay *relay;
};

#endif // MODELVIEWPANEL_H
