#ifndef MODELVIEWPANEL_H
#define MODELVIEWPANEL_H

#include "gui/GuiPanel.h"

#include "views/modelview/ModelViewState.h"

#include <QtCore/QHash>

#include <pcx/scoped_lock.h>

class Model;
class Graphics;
class ModelView;
class Relay;
class GuiComboBox;
class QMenu;

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
    void updateMenu();

    void comboChanged(int index);
    void renderChanged(bool state);

private:
    Model *model;
    Graphics *graphics;
    ModelView *view;
    Relay *relay;
    GuiComboBox *combo;
    QMenu *render;

    QHash<Projection::Type, ModelViewState> states;
    pcx::lock lock;
};

#endif // MODELVIEWPANEL_H
