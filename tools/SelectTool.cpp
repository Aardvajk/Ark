#include "SelectTool.h"

#include "actions/ActionList.h"

#include "graphics/RenderPrimitives.h"

#include "views/ModelView.h"

#include <QPxActions/QPxAction.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

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

void SelectTool::mousePressed(ModelView *view, QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mq.begin(view, event);
    }
}

void SelectTool::mouseMoved(ModelView *view, QMouseEvent *event)
{
    mq.update(view, event);
}

void SelectTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(mq.active(view))
    {
        mq.end(view);
    }
}

void SelectTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mq.active(view))
    {
        RenderPrimitives::invertBox(graphics, params, mq.anchor(), mq.position());
    }
}
