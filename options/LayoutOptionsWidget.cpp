#include "LayoutOptionsWidget.h"

#include "options/components/LayoutDiagram.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxValueButtons.h>

#include <QtWidgets/QGroupBox>

LayoutOptionsWidget::LayoutOptionsWidget(ActionList *actions, QWidget *parent) : QWidget(parent)
{
    auto layout = new QPx::VBoxLayout(8, 8, this);
    auto group = new QPx::VBoxLayout(8, 8, layout->addTypedWidget(new QGroupBox("Panels")));

    diagram = group->addTypedWidget(new LayoutDiagram(actions));

    auto buttons = new QPx::HBoxLayout(0, 8);
    group->addLayout(buttons);

    buttons->addStretch();
    connect(buttons->addTypedWidget(new QPx::BoolButton("&Show All", true)), SIGNAL(valueClicked(bool)), diagram, SLOT(showAll(bool)));
    connect(buttons->addTypedWidget(new QPx::BoolButton("&Hide All", false)), SIGNAL(valueClicked(bool)), diagram, SLOT(showAll(bool)));

    connect(diagram, SIGNAL(changed()), SIGNAL(changed()));
}

void LayoutOptionsWidget::commit()
{
    diagram->commit();
}
