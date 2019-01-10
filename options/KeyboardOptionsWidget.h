#ifndef KEYBOARDOPTIONSWIDGET_H
#define KEYBOARDOPTIONSWIDGET_H

#include "options/OptionsWidget.h"

class ActionList;

namespace QPx
{

class KeyboardOptionsWidget;

}

class KeyboardOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    KeyboardOptionsWidget(ActionList *actions, QWidget *parent = nullptr);

public slots:
    virtual void commit() override;

private:
    QPx::KeyboardOptionsWidget *keyboard;
};

#endif // KEYBOARDOPTIONSWIDGET_H
