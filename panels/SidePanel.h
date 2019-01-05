#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include "gui/GuiPanel.h"

class SidePanel : public GuiPanel
{
    Q_OBJECT

public:
    explicit SidePanel(QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual SidePanel *clone() const override;
};

#endif // SIDEPANEL_H
