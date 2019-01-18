#ifndef SIDEVIEWPANEL_H
#define SIDEVIEWPANEL_H

#include "gui/GuiPanel.h"

class Relay;
class PropertyModel;

class SideViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    SideViewPanel(Relay *relay, PropertyModel *properties, QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual SideViewPanel *clone() const override;

private:
    Relay *relay;
    PropertyModel *properties;
};

#endif // SIDEVIEWPANEL_H
