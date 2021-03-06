#include "GuiButton.h"

#include <QPxCore/QPxUnitAnimation.h>

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QIcon>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QGraphicsColorizeEffect>

namespace
{

class Cache
{
public:
    explicit Cache(QObject *parent) : anim(new QPx::UnitAnimation(400, parent)), menu(nullptr), disable(new QGraphicsColorizeEffect(parent)), down(false), within(false), checkable(false), checked(false) { }

    QString text;
    QIcon icon;
    QPx::UnitAnimation *anim;
    QMenu *menu;
    QGraphicsColorizeEffect *disable;
    bool down, within, checkable, checked;
};

}

GuiButton::GuiButton(QWidget *parent) : QWidget(parent)
{
    auto &c = cache.alloc<Cache>(this);
    setAttribute(Qt::WA_Hover);

    c.disable->setColor(QColor(80, 80, 80));
    c.disable->setEnabled(false);

    setGraphicsEffect(c.disable);

    connect(c.anim, SIGNAL(currentValueChanged(float)), SLOT(update()));
}

QMenu *GuiButton::setMenu(QMenu *menu)
{
    cache.get<Cache>().menu = menu;
    connect(menu, SIGNAL(aboutToHide()), SLOT(reset()));

    return menu;
}

QString GuiButton::text() const
{
    return cache.get<Cache>().text;
}

QIcon GuiButton::icon() const
{
    return cache.get<Cache>().icon;
}

QMenu *GuiButton::menu() const
{
    return cache.get<Cache>().menu;
}

bool GuiButton::isChecked() const
{
    return cache.get<Cache>().checked;
}

void GuiButton::setText(const QString &text)
{
    cache.get<Cache>().text = text;
    update();
}

void GuiButton::setIcon(const QIcon &icon)
{
    cache.get<Cache>().icon = icon;
    update();
}

void GuiButton::setCheckable(bool state)
{
    cache.get<Cache>().checkable = state;
}

void GuiButton::setChecked(bool state)
{
    auto &c = cache.get<Cache>();
    if(c.checkable)
    {
        auto old = c.checked;
        c.checked = state;

        update();

        if(old != state)
        {
            emit toggled(state);
        }
    }
}

void GuiButton::reset()
{
    auto &c = cache.get<Cache>();

    c.down = false;
    c.anim->reset();

    update();
}

void GuiButton::paintEvent(QPaintEvent *event)
{
    auto &c = cache.get<Cache>();

    QPainter painter(this);

    if(autoFillBackground())
    {
        painter.fillRect(rect(), palette().color(QPalette::Window));
    }

    auto hover = QApplication::instance()->property("gui-hover-color").value<QColor>();
    hover.setAlphaF(c.anim->currentValue());

    bool down = (c.down && c.within) || c.checked;

    painter.fillRect(rect(), down ? QApplication::instance()->property("gui-hilight-color").value<QColor>() : hover);
}

bool GuiButton::event(QEvent *event)
{
    auto &c = cache.get<Cache>();

    if(event->type() == QEvent::EnabledChange)
    {
        c.disable->setEnabled(!isEnabled());

        if(!isEnabled())
        {
            if(c.menu) c.menu->close();
            reset();
        }
    }

    if(isEnabled())
    {
        switch(event->type())
        {
            case QEvent::HoverEnter: c.anim->activate(true); break;
            case QEvent::HoverLeave: c.anim->activate(false); break;

            case QEvent::MouseButtonPress: if(static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) buttonPressed(); break;
            case QEvent::MouseButtonRelease: if(static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) buttonReleased(); break;
            case QEvent::MouseMove: c.within = QRect(QPoint(0, 0), size()).contains(static_cast<QMouseEvent*>(event)->pos()); update(); break;

            default: break;
        }
    }

    return QWidget::event(event);
}

void GuiButton::buttonPressed()
{
    auto &c = cache.get<Cache>();

    c.down = c.within = true;
    update();

    if(c.menu)
    {
        c.menu->exec(mapToGlobal(QPoint(0, height())));
    }
    else
    {
        emit pressed();
    }
}

void GuiButton::buttonReleased()
{
    auto &c = cache.get<Cache>();

    c.down = false;
    update();

    if(c.within && c.checkable)
    {
        c.checked = !c.checked;
        emit toggled(c.checked);
    }

    if(c.within && !c.checkable && !c.menu)
    {
        emit clicked();
    }
}
