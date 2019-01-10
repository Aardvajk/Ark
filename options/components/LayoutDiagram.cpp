#include "LayoutDiagram.h"

#include "actions/ActionList.h"

#include <QPxCore/QPxUnitAnimation.h>

#include <QtGui/QPainter>
#include <QtGui/QHoverEvent>
#include <QtGui/QMouseEvent>

namespace
{

class Section
{
public:
    enum Type { LeftTools, RightTools, LeftSide, RightSide, Invalid };

    Section(Type type, ActionList *actions, QWidget *parent);

    Type type;
    QString action;
    QRect rect;
    QPx::UnitAnimation *hoverAnim;
    QPx::UnitAnimation *panelAnim;
    bool hover, state;
};

Section::Section(Type type, ActionList *actions, QWidget *parent) : type(type), hoverAnim(new QPx::UnitAnimation(150, parent)), panelAnim(new QPx::UnitAnimation(400, parent)), hover(false)
{
    static const char *s[] = { "Layout.Left.Tools", "Layout.Right.Tools", "Layout.Left.Sidebar", "Layout.Right.Sidebar" };

    action = s[static_cast<int>(type)];

    state = actions->find(action)->isChecked();
    if(state)
    {
        panelAnim->setCurrentTime(panelAnim->duration());
    }

    QObject::connect(hoverAnim, SIGNAL(currentValueChanged(float)), parent, SLOT(update()));
    QObject::connect(panelAnim, SIGNAL(currentValueChanged(float)), parent, SLOT(update()));
}

class Cache
{
public:
    Cache(ActionList *actions, QWidget *parent);

    QRect sectionRect(Section::Type type) const;
    void updateMousePosition(const QPoint &pos);
    Section::Type find(const QPoint &pos) const;

    ActionList *actions;

    QRect mainRect;
    QList<Section> sections;
    Section::Type curr;

    int barHeight;
    int toolsWidth;
    int toolsHeight;
    int sideWidth;
};

Cache::Cache(ActionList *actions, QWidget *parent) : actions(actions), curr(Section::Type::Invalid)
{
    for(int i = 0; i < Section::Invalid; ++i)
    {
        sections.append(Section(Section::Type(i), actions, parent));
    }

    barHeight = 12;
    toolsWidth = 32;
    toolsHeight = 26;
    sideWidth = 120;
}

QRect Cache::sectionRect(Section::Type type) const
{
    auto rect = sections[type].rect;
    if(type == Section::LeftTools || type == Section::RightTools)
    {
        rect.moveTop(rect.top() + barHeight);
    }

    return rect;
}

void Cache::updateMousePosition(const QPoint &pos)
{
    for(auto &section: sections)
    {
        bool state = sectionRect(section.type).contains(pos);
        if(state != section.hover)
        {
            section.hover = state;
            section.hoverAnim->activate(state);
        }
    }
}

Section::Type Cache::find(const QPoint &pos) const
{
    for(auto &section: sections)
    {
        if(sectionRect(section.type).contains(pos)) return section.type;
    }

    return Section::Invalid;
}

void drawCornerButton(QPainter &painter, const QRect &rect)
{
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(170, 170, 170));

    auto button = rect.adjusted(rect.width() - rect.height(), 0, 0, 0);

    painter.drawRoundRect(button.adjusted(3, 3, -2, -2), 40, 40);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void drawToolButton(QPainter &painter, const QRect &rect)
{
    int dim = (rect.height() / 3) * 2;
    auto button = QRect(rect.left() + ((rect.width() - dim) / 2), rect.top() + (dim / 3), dim + 1, dim + 1);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(170, 170, 170));

    painter.drawRoundRect(button.adjusted(3, 3, -2, -2), 40, 40);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void drawToolButtons(QPainter &painter, const QRect &rect, int height)
{
    auto button = rect.adjusted(0, 0, 0, -(rect.height() - height));
    drawToolButton(painter, button);

    button.moveTop(button.top() + height);
    drawToolButton(painter, button);

    button.moveTop(button.top() + height);
    drawToolButton(painter, button);
}

}

LayoutDiagram::LayoutDiagram(ActionList *actions, QWidget *parent) : QWidget(parent)
{
    cache.alloc<Cache>(actions, this);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    setAttribute(Qt::WA_Hover);
    setAttribute(Qt::WA_MouseTracking);
}

void LayoutDiagram::commit()
{
    auto &c = cache.get<Cache>();

    for(auto &section: c.sections)
    {
        c.actions->find(section.action)->setChecked(section.state);
    }
}

void LayoutDiagram::showAll(bool state)
{
    bool any = false;

    for(auto &section: cache.get<Cache>().sections)
    {
        if(section.state != state)
        {
            section.state = state;
            section.panelAnim->activate(state);

            any = true;
        }
    }

    if(any)
    {
        emit changed();
    }
}

void LayoutDiagram::resizeEvent(QResizeEvent *event)
{
    auto &c = cache.get<Cache>();

    c.mainRect = rect().adjusted(0, 0, -1, -1);

    for(auto &section: c.sections)
    {
        section.rect = c.mainRect;

        switch(section.type)
        {
            case Section::LeftTools: section.rect.setWidth(c.toolsWidth); break;
            case Section::RightTools: section.rect.setWidth(c.toolsWidth); section.rect.moveLeft(c.mainRect.right() - (c.toolsWidth - 1)); break;

            case Section::LeftSide: section.rect.setWidth(c.sideWidth); section.rect.moveLeft(c.toolsWidth); break;
            case Section::RightSide: section.rect.setWidth(c.sideWidth); section.rect.moveLeft(c.mainRect.right() - ((c.toolsWidth - 1) + c.sideWidth)); break;

            default: break;
        }
    }
}

void LayoutDiagram::paintEvent(QPaintEvent *event)
{
    auto &c = cache.get<Cache>();

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    auto panel = QColor(240, 240, 240);
    auto border = QColor(170, 170, 170);

    painter.setPen(border);
    painter.setBrush(QBrush(panel, Qt::DiagCrossPattern));

    painter.drawRect(c.mainRect);

    painter.setBrush(panel);
    painter.setPen(Qt::NoPen);

    painter.drawRect(c.mainRect.adjusted(0, 0, 0, -(c.mainRect.height() - c.barHeight)));

    for(auto &section: c.sections)
    {
        painter.setPen(Qt::NoPen);

        if(section.panelAnim->currentValue() > 0)
        {
            painter.setOpacity(section.panelAnim->currentValue());

            painter.setBrush(panel);
            painter.drawRect(section.rect.adjusted(1, c.barHeight + 1, 0, 0));

            painter.setOpacity(1);
        }

        if(section.hoverAnim->currentValue() > 0)
        {
            auto hover = QColor(210, 230, 250);
            hover.setAlphaF(0.5f * section.hoverAnim->currentValue());

            painter.setBrush(hover);
            painter.drawRect(section.rect.adjusted(1, section.type == Section::LeftTools || section.type == Section::RightTools ? c.barHeight : 1, 0, 0));
        }
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(border);

    painter.drawRect(c.mainRect.adjusted(0, 0, 0, -(c.mainRect.height() - c.barHeight)));

    for(auto &section: c.sections)
    {
        painter.setPen(border);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(section.rect);

        if(section.panelAnim->currentValue() > 0)
        {
            painter.setOpacity(section.panelAnim->currentValue());

            if(section.type == Section::LeftSide || section.type == Section::RightSide)
            {
                drawCornerButton(painter, section.rect.adjusted(0, 0, 0, -(section.rect.height() - c.barHeight)));

                auto rect = section.rect;

                rect.moveTop(((c.mainRect.height() / 4) * 2) - c.barHeight);
                rect.setHeight(c.barHeight);

                painter.setPen(border);
                painter.setBrush(Qt::NoBrush);

                painter.drawRect(rect);
                drawCornerButton(painter, rect);
            }
            else if(section.type == Section::LeftTools || section.type == Section::RightTools)
            {
                drawToolButtons(painter, section.rect.adjusted(1, c.barHeight + 1, 0, 0), c.toolsHeight);
            }

            painter.setOpacity(1);
        }
    }
}

bool LayoutDiagram::event(QEvent *event)
{
    auto &c = cache.get<Cache>();

    switch(event->type())
    {
        case QEvent::HoverEnter:
        case QEvent::HoverLeave: c.updateMousePosition(static_cast<QHoverEvent*>(event)->pos()); break;

        case QEvent::MouseMove: c.updateMousePosition(static_cast<QMouseEvent*>(event)->pos()); break;

        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease: button(static_cast<QMouseEvent*>(event), event->type() == QEvent::MouseButtonPress); break;

        default: break;
    }

    return QWidget::event(event);
}

void LayoutDiagram::button(QMouseEvent *event, bool down)
{
    auto &c = cache.get<Cache>();
    auto section = c.find(event->pos());

    if(down)
    {
        c.curr = section;
    }
    else
    {
        if(c.curr == section)
        {
            if(section != Section::Invalid)
            {
                auto &panel = c.sections[section];

                panel.state = !panel.state;
                panel.panelAnim->activate(panel.state);

                update();
                emit changed();
            }
        }
    }
}
