#include "ToolList.h"

#include "core/Relay.h"

#include "tools/Tool.h"

ToolList::ToolList(Relay *relay, QObject *parent) : QObject(parent), relay(relay)
{
    connect(this, SIGNAL(toolAdded(Tool*)), relay, SIGNAL(toolAdded(Tool*)));
}

Tool *ToolList::addTool(Tool *tool)
{
    tool->setParent(this);
    data.append(tool);

    connect(tool, SIGNAL(selected(Tool*)), relay, SIGNAL(toolSelected(Tool*)));

    emit toolAdded(tool);

    return tool;
}
