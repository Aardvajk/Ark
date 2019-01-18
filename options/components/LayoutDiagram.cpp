#include "LayoutDiagram.h"

#include <QPxCore/QPxUnitAnimation.h>

#include <QtGui/QPainter>
#include <QtGui/QHoverEvent>
#include <QtGui/QMouseEvent>

namespace
{

class Section
{
public:
    Section() : type(LayoutDiagram::Type::Invalid) { }
    Section(LayoutDiagram::Type type, QWidget *parent);

    LayoutDiagram::Type type;
    QRect rect;
    QPx::UnitAnimation *hoverAnim;
    QPx::UnitAnimation *panelAnim;
    bool hover, state;
};

Section::Section(LayoutDiagram::Type type, QWidget *parent) : type(type), hoverAnim(new QPx::UnitAnimation(400, parent)), panelAnim(new QPx::UnitAnimation(200, parent)), hover(false), state(false)
{
    QObject::connect(hoverAnim, SIGNAL(currentValueChanged(float)), parent, SLOT(update()));
    QObject::connect(panelAnim, SIGNAL(currentValueChanged(float)), parent, SLOT(update()));
}

class Cache
{
public:
    explicit Cache(QWidget *parent);

    QRect sectionRect(LayoutDiagram::Type type) const;
    void updateMousePosition(const QPoint &pos);
    LayoutDiagram::Type find(const QPoint &pos) const;

    QRect mainRect;
    QVector<Section> sections;
    LayoutDiagram::Type curr;

    int barHeight;
    int toolsWidth;
    int toolsHeight;
    int sideWidth;
};

Cache::Cache(QWidget *parent) : curr(LayoutDiagram::Type::Invalid), barHeight(12), toolsWidth(32), toolsHeight(26), sideWidth(120)
{
    for(int i = 0; i < static_cast<int>(LayoutDiagram::Type::Invalid); ++i)
    {
        sections.append(Section(static_cast<LayoutDiagram::Type>(i), parent));
    }
}

QRect Cache::sectionRect(LayoutDiagram::Type type) const
{
    auto rect = sections[static_cast<int>(type)].rect;
    if(type == LayoutDiagram::Type::LeftTools || type == LayoutDiagram::Type::RightTools)
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

LayoutDiagram::Type Cache::find(const QPoint &pos) const
{
    for(auto &section: sections)
    {
        if(sectionRect(section.type).contains(pos)) return section.type;
    }

    return LayoutDiagram::Type::Invalid;
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

    for(int i = 0; i < 3; ++i)
    {
        drawToolButton(painter, button);
        button.moveTop(button.top() + height);
    }
}

}

LayoutDiagram::LayoutDiagram(QWidget *parent) : QWidget(parent)
{
    cache.alloc<Cache>(this);

    setAttribute(Qt::WA_Hover);
    setAttribute(Qt::WA_MouseTracking);
}

bool LayoutDiagram::state(Type type) const
{
    return cache.get<Cache>().sections[static_cast<int>(type)].state;
}

void LayoutDiagram::setState(LayoutDiagram::Type type, bool state)
{
    auto &section = cache.get<Cache>().sections[static_cast<int>(type)];

    if(section.state != state)
    {
        section.state = state;
        section.panelAnim->activate(state);

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
            case LayoutDiagram::Type::LeftTools: section.rect.setWidth(c.toolsWidth); break;
            case LayoutDiagram::Type::RightTools: section.rect.setWidth(c.toolsWidth); section.rect.moveLeft(c.mainRect.right() - (c.toolsWidth - 1)); break;

            case LayoutDiagram::Type::LeftSidebar: section.rect.setWidth(c.sideWidth); section.rect.moveLeft(c.toolsWidth); break;
            case LayoutDiagram::Type::RightSidebar: section.rect.setWidth(c.sideWidth); section.rect.moveLeft(c.mainRect.right() - ((c.toolsWidth - 1) + c.sideWidth)); break;

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
    auto hilight = QColor(210, 230, 250);

    painter.setPen(border);
    painter.setBrush(QBrush(hilight, Qt::DiagCrossPattern));

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
            auto hover = hilight;
            hover.setAlphaF(0.7f * section.hoverAnim->currentValue());

            painter.setBrush(hover);
            painter.drawRect(section.rect.adjusted(1, section.type == LayoutDiagram::Type::LeftTools || section.type == LayoutDiagram::Type::RightTools ? c.barHeight : 1, 0, 0));
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

            if(section.type == LayoutDiagram::Type::LeftSidebar || section.type == LayoutDiagram::Type::RightSidebar)
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
            else if(section.type == LayoutDiagram::Type::LeftTools || section.type == LayoutDiagram::Type::RightTools)
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
            if(section != LayoutDiagram::Type::Invalid)
            {
                auto &panel = c.sections[static_cast<int>(section)];

                panel.state = !panel.state;
                panel.panelAnim->activate(panel.state);

                update();
                emit changed();
            }
        }
    }
}
