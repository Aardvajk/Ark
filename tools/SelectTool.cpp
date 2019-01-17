#include "SelectTool.h"

#include "actions/ActionList.h"

#include "graphics/RenderPrimitives.h"

#include "views/ModelView.h"

#include "controls/SettingsElementBox.h"
#include "controls/SettingsCheckBox.h"

#include <QPxCore/QPxSettings.h>

#include <QPxActions/QPxAction.h>

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QPixmap>
#include <QtGui/QMouseEvent>

SelectTool::SelectTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent) : Tool(settings, parent)
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

void SelectTool::addOptions(QPx::VBoxLayout *layout) const
{
    layout->addWidget(new SettingsElementBox(settings["Element.Type"]));
    layout->addWidget(new SettingsCheckBox(settings["Visible.Only"], "Visible Only"));
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
    if(mq.active(view) && event->button() == Qt::LeftButton)
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

void SelectTool::focusLost()
{
    mq.end(mq.widget());
}
