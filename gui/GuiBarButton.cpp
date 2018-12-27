#include "GuiBarButton.h"

#include "gui/GuiBar.h"

#include <QPxCore/QPxAnimations.h>

#include <QtCore/QEvent>

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QGraphicsColorizeEffect>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

namespace
{

class Cache
{
public:
    Cache(GuiBar *bar, GuiBarButton *button, const QString &text, QMenu *menu, const QPixmap &pix);

    GuiBar *bar;
    QPx::UnitAnimation *anim;
    QMenu *menu;
    bool down, within, checkable, checked;
    QString text;
    QPixmap pix;
    int pixDim;
    QGraphicsColorizeEffect *disableEffect;
};

Cache::Cache(GuiBar *bar, GuiBarButton *button, const QString &text, QMenu *menu, const QPixmap &pix) : bar(bar), menu(menu), down(false), within(false), checkable(false), checked(false), text(text), pix(pix)
{
    anim = new QPx::UnitAnimation(200, 500, button);

    pixDim = bar->type() == GuiBar::Type::Small ? 16 : 24;

    button->setAttribute(Qt::WA_Hover);
    button->setFixedSize(bar->defaultButtonSize());

    QObject::connect(anim, SIGNAL(valueChanged(QVariant)), button, SLOT(update()));

    disableEffect = new QGraphicsColorizeEffect(button);
    disableEffect->setColor(Qt::darkGray);
    disableEffect->setEnabled(false);

    button->setGraphicsEffect(disableEffect);
}

}

GuiBarButton::GuiBarButton(const QPixmap &pixmap, GuiBar *parent) : QWidget(parent)
{
    auto &c = cache.alloc<Cache>(parent, this, QString(), nullptr, pixmap);
}

GuiBarButton::GuiBarButton(const QString &text, const QPixmap &pixmap, GuiBar *parent) : QWidget(parent)
{
    auto &c = cache.alloc<Cache>(parent, this, text, nullptr, pixmap);
}

GuiBarButton::GuiBarButton(QMenu *menu, const QPixmap &pixmap, GuiBar *parent)
{
    auto &c = cache.alloc<Cache>(parent, this, QString(), menu, pixmap);
    connect(menu, SIGNAL(aboutToHide()), SLOT(reset()));
}

void GuiBarButton::setCheckable(bool state)
{
    cache.get<Cache>().checkable = state;
}

bool GuiBarButton::isCheckable() const
{
    return cache.get<Cache>().checkable;
}

bool GuiBarButton::isChecked() const
{
    return cache.get<Cache>().checked;
}

void GuiBarButton::click()
{
    emit clicked();
}

void GuiBarButton::setChecked(bool state)
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

void GuiBarButton::toggle()
{
    auto &c = cache.get<Cache>();
    if(c.checkable)
    {
        c.checked = !c.checked;
        update();

        emit toggled(c.checked);
    }
}

bool GuiBarButton::event(QEvent *event)
{
    auto &c = cache.get<Cache>();

    if(event->type() == QEvent::EnabledChange)
    {
        c.disableEffect->setEnabled(!isEnabled());
        if(!isEnabled())
        {
            c.anim->reset();
        }
    }

    if(isEnabled())
    {
        switch(event->type())
        {
            case QEvent::HoverEnter: c.anim->activate(); break;
            case QEvent::HoverLeave: c.checked ? c.anim->reset() : c.anim->deactivate(); break;
            case QEvent::MouseButtonPress: if(static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) buttonPressed(); break;
            case QEvent::MouseButtonRelease: if(static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton) buttonReleased(); break;
            case QEvent::MouseMove: c.within = QRect(QPoint(0, 0), size()).contains(static_cast<QMouseEvent*>(event)->pos()); update(); break;

            default: break;
        }
    }

    return QWidget::event(event);
}

void GuiBarButton::paintEvent(QPaintEvent *event)
{
    auto &c = cache.get<Cache>();
    QPainter painter(this);

    bool down = (c.down && c.within) || c.checked;

    auto hover = qvariant_cast<QColor>(QApplication::instance()->property("gui-hover"));
    hover.setAlphaF(c.anim->currentValue().toFloat());

    painter.fillRect(rect(), down ? qvariant_cast<QColor>(QApplication::instance()->property("gui-hilight")) : hover);

    if(c.bar->type() == GuiBar::Type::Small)
    {
        int x = (rect().width() - c.pixDim) / 2;
        int y = (rect().height() - c.pixDim) / 2;

        painter.drawPixmap(x, y, c.pixDim, c.pixDim, c.pix);
    }
    else
    {
        int x = (rect().width() - c.pixDim) / 2;
        int y = 8;

        painter.drawPixmap(x, y, c.pixDim, c.pixDim, c.pix);

        auto font = painter.font();
        font.setBold(true);
        font.setPointSize(7);

        painter.setFont(font);

        QRect r(0, y + c.pixDim + 2, rect().width(), QFontMetrics(font).height());

        painter.setPen(qvariant_cast<QColor>(QApplication::instance()->property("gui-text")));
        painter.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, c.text);
    }
}

void GuiBarButton::reset()
{
    auto &c = cache.get<Cache>();

    c.down = false;
    c.anim->reset();
}

void GuiBarButton::buttonPressed()
{
    auto &c = cache.get<Cache>();

    c.within = c.down = true;
    update();

    if(c.menu)
    {
        c.menu->exec(mapToGlobal(QPoint(0, height())));
    }
}

void GuiBarButton::buttonReleased()
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
