#include "ToolList.h"

#include "core/Relay.h"

#include "tools/Tool.h"

namespace
{

void homogenousConnect(QObject *sender, const char *signal, QObject *receiver, const char *slot)
{
    QObject::connect(sender, signal, receiver, slot);
}

void homogenousDisconnect(QObject *sender, const char *signal, QObject *receiver, const char *slot)
{
    QObject::disconnect(sender, signal, receiver, slot);
}

void updateConnections(QObject *sender, QObject *receiver, void(*func)(QObject*,const char*,QObject*,const char*))
{
    static const char *send[] = { SIGNAL(mousePressed(ModelView*,QMouseEvent*)), SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), SIGNAL(render(ModelView*,Graphics*,const RenderParams&)), "" };
    static const char *recv[] = { SLOT(mousePressed(ModelView*,QMouseEvent*)), SLOT(mouseMoved(ModelView*,QMouseEvent*)), SLOT(mouseReleased(ModelView*,QMouseEvent*)), SLOT(render(ModelView*,Graphics*,const RenderParams&)) };

    auto i = 0;
    while(send[i][0])
    {
        func(sender, send[i], receiver, recv[i]);
        ++i;
    }
}

}

ToolList::ToolList(Relay *relay, QObject *parent) : QObject(parent), relay(relay), curr(nullptr)
{
    connect(this, SIGNAL(toolAdded(Tool*)), relay, SIGNAL(toolAdded(Tool*)));
}

Tool *ToolList::addTool(Tool *tool)
{
    tool->setParent(this);

    connect(tool, SIGNAL(selected(Tool*)), relay, SIGNAL(toolSelected(Tool*)));
    connect(tool, SIGNAL(selected(Tool*)), this, SLOT(toolSelected(Tool*)));

    emit toolAdded(tool);
    return tool;
}

void ToolList::toolSelected(Tool *tool)
{
    if(curr)
    {
        curr->focusLost();
        updateConnections(relay, curr, homogenousDisconnect);
    }

    curr = tool;

    if(curr)
    {
        updateConnections(relay, curr, homogenousConnect);
    }
}
