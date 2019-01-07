#ifndef SIDEVIEWPANEL_H
#define SIDEVIEWPANEL_H

#include "gui/GuiPanel.h"

class SideViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    explicit SideViewPanel(QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual SideViewPanel *clone() const override;
};

#endif // SIDEVIEWPANEL_H
