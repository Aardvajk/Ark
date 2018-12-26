#ifndef MODELVIEWPANEL_H
#define MODELVIEWPANEL_H

#include "panels/Panel.h"

class Model;
class Graphics;
class ModelView;

class ModelViewPanel : public Panel
{
public:
    ModelViewPanel(Model *model, Graphics *graphics, QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;

protected:
    virtual ModelViewPanel *clone() const override;

private:
    Model *model;
    Graphics *graphics;
    ModelView *view;
};

#endif // MODELVIEWPANEL_H
