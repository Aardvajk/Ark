#include "MoveTool.h"

#include "actions/ActionList.h"

#include <QPxCore/QPxAction.h>

#include <QtGui/QPixmap>

MoveTool::MoveTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent)
{
    connect(actions->add("Tools.Move", "Move", QKeySequence("2")), SIGNAL(triggered()), SLOT(select()));
}

QString MoveTool::name() const
{
    return "Move";
}

QIcon MoveTool::icon() const
{
    return QIcon(":/resources/images/ark.png");
}
