#include "LayoutOptionsWidget.h"

#include "actions/ActionList.h"

#include "options/components/LayoutDiagram.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxValueButtons.h>

#include <QtWidgets/QGroupBox>

LayoutOptionsWidget::LayoutOptionsWidget(ActionList *actions, QWidget *parent) : QWidget(parent)
{
    auto layout = new QPx::VBoxLayout(8, 8, this);
    auto group = new QPx::VBoxLayout(8, 8, layout->addTypedWidget(new QGroupBox("Panels")));

    diagram = group->addTypedWidget(new LayoutDiagram());

    auto buttons = new QPx::HBoxLayout(0, 8);
    group->addLayout(buttons);

    buttons->addStretch();
    connect(buttons->addTypedWidget(new QPx::ValueButton("&Show All", true)), SIGNAL(clicked(QVariant)), SLOT(showAll(QVariant)));
    connect(buttons->addTypedWidget(new QPx::ValueButton("&Hide All", false)), SIGNAL(clicked(QVariant)), SLOT(showAll(QVariant)));

    diagram->setState(LayoutDiagram::Type::LeftTools, actions->find("Layout.Left.Tools")->isChecked());
    diagram->setState(LayoutDiagram::Type::RightTools, actions->find("Layout.Right.Tools")->isChecked());
    diagram->setState(LayoutDiagram::Type::LeftSidebar, actions->find("Layout.Left.Sidebar")->isChecked());
    diagram->setState(LayoutDiagram::Type::RightSidebar, actions->find("Layout.Right.Sidebar")->isChecked());

    connect(diagram, SIGNAL(changed()), SIGNAL(changed()));
}

void LayoutOptionsWidget::commit()
{
}

void LayoutOptionsWidget::showAll(const QVariant &state)
{
    diagram->setState(LayoutDiagram::Type::LeftTools, state.toBool());
    diagram->setState(LayoutDiagram::Type::RightTools, state.toBool());
    diagram->setState(LayoutDiagram::Type::LeftSidebar, state.toBool());
    diagram->setState(LayoutDiagram::Type::RightSidebar, state.toBool());
}
