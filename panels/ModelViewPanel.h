#ifndef MODELVIEWPANEL_H
#define MODELVIEWPANEL_H

#include "gui/GuiPanel.h"

class Model;
class Graphics;
class ModelView;
class Relay;

class ModelViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    ModelViewPanel(Model *model, Graphics *graphics, Relay *relay, QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual ModelViewPanel *clone() const override;

private slots:
    void projectionChanged(int index);

private:
    Model *model;
    Graphics *graphics;
    ModelView *view;
    Relay *relay;
};

#endif // MODELVIEWPANEL_H
