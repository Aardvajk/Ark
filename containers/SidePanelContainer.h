#ifndef SIDEPANELCONTAINER_H
#define SIDEPANELCONTAINER_H

#include "gui/GuiContainer.h"

class SidePanelContainer : public GuiContainer
{
public:
    explicit SidePanelContainer(QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;
};

#endif // SIDEPANELCONTAINER_H
