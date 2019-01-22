#include "ToolView.h"

#include "core/Relay.h"

#include "gui/GuiLargeButton.h"
#include "gui/GuiButtonGroup.h"

#include "tools/Tool.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

ToolView::ToolView(Relay *relay, QWidget *parent) : QWidget(parent), group(new GuiButtonGroup(this))
{
    layout = new QPx::VBoxLayout(this);

    QPx::setPaletteColor(this, QPalette::Window, QApplication::instance()->property("gui-panel-color").value<QColor>());
    setAutoFillBackground(true);

    layout->addStretch();

    connect(relay, SIGNAL(toolAdded(Tool*)), SLOT(toolAdded(Tool*)));
    connect(relay, SIGNAL(toolSelected(Tool*)), SLOT(toolSelected(Tool*)));
}

void ToolView::toolAdded(Tool *tool)
{
    auto button = group->addButton(new GuiLargeButton(tool->name(), tool->icon(), this));
    button->setProperty("ark-tool", QVariant::fromValue(tool));

    connect(button, SIGNAL(toggled(bool)), SLOT(buttonToggled(bool)));

    mapping[tool] = button;
    layout->insertWidget(layout->count() - 1, button);
}

void ToolView::toolSelected(Tool *tool)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        mapping[tool]->setChecked(true);
    }
}

void ToolView::buttonToggled(bool state)
{
    if(!lock && state)
    {
        auto s = pcx::scoped_lock(lock);
        qvariant_cast<Tool*>(sender()->property("ark-tool"))->select();
    }
}
