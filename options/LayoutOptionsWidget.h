#ifndef LAYOUTOPTIONSWIDGET_H
#define LAYOUTOPTIONSWIDGET_H

#include "options/OptionsWidget.h"

class ActionList;
class LayoutDiagram;
class QPushButton;

class LayoutOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    LayoutOptionsWidget(ActionList *actions, QWidget *parent = nullptr);

public slots:
    virtual void commit() override;
    void setStates(const QVariant &state);

private slots:
    void stateChanged();

private:
    ActionList *actions;
    LayoutDiagram *diagram;

    QPushButton *showButton;
    QPushButton *hideButton;
};

#endif // LAYOUTOPTIONSWIDGET_H
