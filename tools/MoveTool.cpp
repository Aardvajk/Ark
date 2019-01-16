#include "MoveTool.h"

#include "actions/ActionList.h"

#include <QPxActions/QPxAction.h>

#include <QtGui/QPixmap>

MoveTool::MoveTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent)
{
    connect(actions->add("Tools.Move", "Move", QKeySequence("2")), SIGNAL(triggered()), SLOT(select()));
}

QString MoveTool::name() const
{
    return "Move";
}

QPixmap MoveTool::icon() const
{
    return QPixmap(":/resources/images/ark.png");
}
