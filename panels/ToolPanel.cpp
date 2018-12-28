#include "ToolPanel.h"

#include "gui/GuiButtonGroup.h"

#include "views/ModelViewRelay.h"

#include "panels/ToolButton.h"

#include "tools/Tool.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

ToolPanel::ToolPanel(ModelViewRelay *relay, QWidget *parent) : QWidget(parent), relay(relay), group(new GuiButtonGroup(this)), current(nullptr)
{
    new QPx::VBoxLayout(this);
    setFixedWidth(QApplication::instance()->property("gui-tool-width").toInt());
}

Tool *ToolPanel::addTool(Tool *tool)
{
    auto button = new ToolButton(tool->name(), tool->icon());
    button->setProperty("ark-tool", QVariant::fromValue(tool));

    layout()->addWidget(group->addButton(button));

    connect(button, SIGNAL(toggled(bool)), SLOT(toggled(bool)));
    connect(tool, SIGNAL(select()), SLOT(selected()));

    return tool;
}

void ToolPanel::addStretch()
{
    static_cast<QBoxLayout*>(layout())->addStretch();
}

void ToolPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), qvariant_cast<QColor>(QApplication::instance()->property("gui-panel-color")));
}

void ToolPanel::toggled(bool state)
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

void ToolPanel::selected()
{
    for(int i = 0; i < layout()->count(); ++i)
    {
        auto widget = layout()->itemAt(i)->widget();

        if(widget && qvariant_cast<Tool*>(widget->property("ark-tool")) == sender())
        {
            static_cast<ToolButton*>(widget)->setChecked(true);
            return;
        }
    }
}
