#include "KeyboardOptionsWidget.h"

#include "actions/ActionList.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxKeyboardOptionsWidget.h>

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

KeyboardOptionsWidget::KeyboardOptionsWidget(ActionList *actions, QWidget *parent) : OptionsWidget(parent)
{
    auto layout = new QPx::VBoxLayout({ }, { }, this);
    auto group = new QPx::VBoxLayout(layout->addTypedWidget(new QGroupBox("Shortcuts")));

    keyboard = group->addTypedWidget(new QPx::KeyboardOptionsWidget(actions));

    connect(keyboard, SIGNAL(changed()), SIGNAL(changed()));
}

void KeyboardOptionsWidget::commit()
{
    keyboard->commit();
}
