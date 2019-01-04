#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H

#include "gui/GuiPanel.h"

class PropertyPanel : public GuiPanel
{
    Q_OBJECT

public:
    explicit PropertyPanel(QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual PropertyPanel *clone() const override;
};

#endif // PROPERTYPANEL_H
