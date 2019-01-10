#include "LayoutOptionsWidget.h"

#include "actions/ActionList.h"

#include "options/components/LayoutDiagram.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxValueButtons.h>

#include <QtWidgets/QGroupBox>

namespace
{

static const char *actionIds[] = { "Layout.Left.Tools", "Layout.Right.Tools", "Layout.Left.Sidebar", "Layout.Right.Sidebar" };

}

LayoutOptionsWidget::LayoutOptionsWidget(ActionList *actions, QWidget *parent) : OptionsWidget(parent), actions(actions)
{
    auto layout = new QPx::VBoxLayout(8, 8, this);
    auto group = new QPx::VBoxLayout(8, 8, layout->addTypedWidget(new QGroupBox("Panels")));

    diagram = group->addTypedWidget(new LayoutDiagram());

    auto buttons = new QPx::HBoxLayout(0, 8);
    group->addLayout(buttons);

    buttons->addStretch();
    connect(buttons->addTypedWidget(new QPx::ValueButton("&Show All", true)), SIGNAL(clicked(QVariant)), SLOT(setStates(QVariant)));
    connect(buttons->addTypedWidget(new QPx::ValueButton("&Hide All", false)), SIGNAL(clicked(QVariant)), SLOT(setStates(QVariant)));

    for(int i = 0; i < static_cast<int>(LayoutDiagram::Type::Invalid); ++i)
    {
        diagram->setState(static_cast<LayoutDiagram::Type>(i), actions->find(actionIds[i])->isChecked());
    }

    connect(diagram, SIGNAL(changed()), SIGNAL(changed()));
}

void LayoutOptionsWidget::commit()
{
    for(int i = 0; i < static_cast<int>(LayoutDiagram::Type::Invalid); ++i)
    {
        actions->find(actionIds[i])->setChecked(diagram->state(static_cast<LayoutDiagram::Type>(i)));
    }
}

void LayoutOptionsWidget::setStates(const QVariant &state)
{
    for(int i = 0; i < static_cast<int>(LayoutDiagram::Type::Invalid); ++i)
    {
        diagram->setState(static_cast<LayoutDiagram::Type>(i), state.toBool());
    }
}
