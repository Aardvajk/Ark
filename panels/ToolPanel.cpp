#include "ToolPanel.h"

#include "gui/GuiButtonGroup.h"
#include "gui/GuiSeparator.h"

#include "views/ModelViewRelay.h"

#include "panels/ToolButton.h"

#include "tools/Tool.h"

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

namespace
{

class Cache
{
public:
    Cache(ToolPanel *parent, ModelViewRelay *relay) : relay(relay), group(new GuiButtonGroup(parent)), current(nullptr) { }

    ModelViewRelay *relay;
    GuiButtonGroup *group;
    Tool *current;

    QList<ToolButton*> toolButtons;
};

}

ToolPanel::ToolPanel(ModelViewRelay *relay, QWidget *parent) : QWidget(parent)
{
    cache.alloc<Cache>(this, relay);
    setFixedWidth(QApplication::instance()->property("gui-tool-width").toInt());
}

Tool *ToolPanel::addTool(Tool *tool)
{
    auto &c = cache.get<Cache>();

    auto button = new ToolButton(tool->name(), tool->icon(), this);
    button->setProperty("ark-tool", QVariant::fromValue(tool));

    c.group->addButton(button);
    c.toolButtons.append(button);

    connect(button, SIGNAL(toggled(bool)), SLOT(toggled(bool)));
    connect(tool, SIGNAL(select()), SLOT(selected()));

    updateGeometry();
    return tool;
}

void ToolPanel::resizeEvent(QResizeEvent *event)
{
    auto &c = cache.get<Cache>();

    int y = 0;
    for(auto button: c.toolButtons)
    {
        button->move(0, y);
        y += button->height();
    }

    QWidget::resizeEvent(event);
}

void ToolPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), qvariant_cast<QColor>(QApplication::instance()->property("gui-panel-color")));
}

void ToolPanel::toggled(bool state)
{
    auto &c = cache.get<Cache>();

    if(c.current)
    {
        c.current->focusLost();

        disconnect(c.relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), c.current, SLOT(mousePressed(ModelView*,QMouseEvent*)));
        disconnect(c.relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), c.current, SLOT(mouseMoved(ModelView*,QMouseEvent*)));
        disconnect(c.relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), c.current, SLOT(mouseReleased(ModelView*,QMouseEvent*)));
        disconnect(c.relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)), c.current, SLOT(render(ModelView*,Graphics*,RenderParams)));
    }

    c.current = qvariant_cast<Tool*>(sender()->property("ark-tool"));

    if(c.current)
    {
        connect(c.relay, SIGNAL(mousePressed(ModelView*,QMouseEvent*)), c.current, SLOT(mousePressed(ModelView*,QMouseEvent*)));
        connect(c.relay, SIGNAL(mouseMoved(ModelView*,QMouseEvent*)), c.current, SLOT(mouseMoved(ModelView*,QMouseEvent*)));
        connect(c.relay, SIGNAL(mouseReleased(ModelView*,QMouseEvent*)), c.current, SLOT(mouseReleased(ModelView*,QMouseEvent*)));
        connect(c.relay, SIGNAL(render(ModelView*,Graphics*,RenderParams)), c.current, SLOT(render(ModelView*,Graphics*,RenderParams)));
    }
}

void ToolPanel::selected()
{
    for(auto button: cache.get<Cache>().toolButtons)
    {
        if(qvariant_cast<Tool*>(button->property("ark-tool")) == sender())
        {
            button->setChecked(true);
            return;
        }
    }
}
