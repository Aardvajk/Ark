#include "SelectTool.h"

#include "actions/ActionList.h"

#include <QPxActions/QPxAction.h>

#include <QtGui/QPixmap>

SelectTool::SelectTool(ActionList *actions, Model *model, QObject *parent) : Tool(parent)
{
    connect(actions->add("Tools.Select", "Select", QKeySequence("1")), SIGNAL(triggered()), SLOT(select()));
}

QString SelectTool::name() const
{
    return "Select";
}

QPixmap SelectTool::icon() const
{
    return QPixmap(":/resources/images/ark.png");
}
