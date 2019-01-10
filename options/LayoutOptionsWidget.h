#ifndef LAYOUTOPTIONSWIDGET_H
#define LAYOUTOPTIONSWIDGET_H

#include "options/OptionsWidget.h"

class ActionList;
class LayoutDiagram;

class LayoutOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    LayoutOptionsWidget(ActionList *actions, QWidget *parent = nullptr);

public slots:
    virtual void commit() override;
    void setStates(const QVariant &state);

private:
    ActionList *actions;
    LayoutDiagram *diagram;
};

#endif // LAYOUTOPTIONSWIDGET_H
