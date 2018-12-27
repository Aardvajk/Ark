#include "MoveTool.h"

#include "actions/ActionList.h"

#include <QtGui/QPixmap>

MoveTool::MoveTool(Model *model, ActionList *actions, QObject *parent) : Tool(parent)
{
    connect(actions->add("Tools.Move", "Move", QKeySequence("2"), QIcon()), SIGNAL(triggered()), SIGNAL(select()));
}

QString MoveTool::name() const
{
    return "Move";
}

QPixmap MoveTool::icon() const
{
    return QPixmap(":/resources/images/ark.png");
}

void MoveTool::mousePressed(ModelView *view, QMouseEvent *event)
{
}

void MoveTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
}

void MoveTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
}

void MoveTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
}
