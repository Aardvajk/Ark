#ifndef SIDEVIEWCONTAINER_H
#define SIDEVIEWCONTAINER_H

#include "gui/GuiContainer.h"

class SideViewContainer : public GuiContainer
{
    Q_OBJECT

public:
    explicit SideViewContainer(QWidget *parent = nullptr);

protected:
    virtual GuiPanel *createPanel() const override;
};

#endif // SIDEVIEWCONTAINER_H
