#include "ToolPanel.h"

#include "gui/GuiBarButton.h"
#include "gui/GuiBarButtonGroup.h"

#include "tools/Tool.h"

#include "views/ModelViewRelay.h"

ToolPanel::ToolPanel(ModelViewRelay *relay, QWidget *parent) : GuiBar(Qt::Vertical, GuiBar::Type::Large, parent), relay(relay), group(new GuiBarButtonGroup(this)), current(nullptr)
{
    addStretch();
}

Tool *ToolPanel::addTool(Tool *tool)
{
    auto button = group->addButton(new GuiBarButton(tool->name(), tool->icon(), this));
    button->setProperty("ark-tool", QVariant::fromValue(tool));

    connect(button, SIGNAL(toggled(bool)), SLOT(toggle(bool)));
    connect(tool, SIGNAL(select()), SLOT(select()));

    insertWidget(group->count() - 1, button);
    mapping[tool] = button;

    return tool;
}

void ToolPanel::select()
{
    mapping[static_cast<Tool*>(sender())]->setChecked(true);
}

void ToolPanel::toggle(bool state)
{
    if(current)
    {
        current->focusLost();

        disconnect(relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), current, SLOT(mousePressed(ModelView*,QMouseEvent*)));
        disconnect(relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), current, SLOT(mouseMoved(ModelView*,QMouseEvent*)));
        disconnect(relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), current, SLOT(mouseReleased(ModelView*,QMouseEvent*)));
        disconnect(relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)), current, SLOT(render(ModelView*,Graphics*,RenderParams)));
    }

    current = qvariant_cast<Tool*>(sender()->property("ark-tool"));

    if(current)
    {
        connect(relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), current, SLOT(mousePressed(ModelView*,QMouseEvent*)));
        connect(relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), current, SLOT(mouseMoved(ModelView*,QMouseEvent*)));
        connect(relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), current, SLOT(mouseReleased(ModelView*,QMouseEvent*)));
        connect(relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)), current, SLOT(render(ModelView*,Graphics*,RenderParams)));
    }
}
