#include "SelectTool.h"

#include "actions/ActionList.h"

#include "graphics/RenderPrimitives.h"

#include "views/ModelView.h"

#include <GxMaths/GxColor.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

SelectTool::SelectTool(Model *model, ActionList *actions, QObject *parent) : Tool(parent)
{
    connect(actions->add("Tools.Select", "Select", QKeySequence("1"), QIcon()), SIGNAL(triggered()), SIGNAL(select()));
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
    if(mq.widget())
    {
        mq.update(event);
    }
}

void SelectTool::mouseReleased(ModelView *view, QMouseEvent *event)
{
    if(mq.widget())
    {
        mq.end();
    }
}

void SelectTool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    if(mq.widget() == view)
    {
        RenderPrimitives::box(graphics, params, mq.anchor(), mq.position(), { 1, 1, 1 });
    }
}

void SelectTool::focusLost()
{
    mq.end();
}
