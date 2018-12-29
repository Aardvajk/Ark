#ifndef PROPERTYVIEWPANEL_H
#define PROPERTYVIEWPANEL_H

#include "gui/GuiPanel.h"

class PropertyViewPanel : public GuiPanel
{
    Q_OBJECT

public:
    explicit PropertyViewPanel(QWidget *parent = nullptr);

    virtual void saveState(QPx::Settings &settings) const override;
    virtual void restoreState(const QPx::Settings &settings) override;

protected:
    virtual PropertyViewPanel *clone() const override;
};

#endif // PROPERTYVIEWPANEL_H
