#include "ViewBarButton.h"

#include "view/ViewBar.h"

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
    Cache(ViewBar *bar, ViewBarButton *button, const QString &text, QMenu *menu, const QPixmap &pix);

    ViewBar::Type type;
    QPx::UnitAnimation *anim;
    QMenu *menu;
    bool down, within, checkable, checked;
    QString text;
    QPixmap pix;
    int pixDim;
    QGraphicsColorizeEffect *disableEffect;
};

Cache::Cache(ViewBar *bar, ViewBarButton *button, const QString &text, QMenu *menu, const QPixmap &pix) : type(bar->type()), menu(menu), down(false), within(false), checkable(false), checked(false), text(text), pix(pix)
{
    anim = new QPx::UnitAnimation(200, 500, button);

    pixDim = bar->type() == ViewBar::Type::Small ? 16 : 24;

    button->setAttribute(Qt::WA_Hover);
    button->setFixedSize(bar->defaultButtonSize());

    QObject::connect(anim, SIGNAL(valueChanged(QVariant)), button, SLOT(update()));

    disableEffect = new QGraphicsColorizeEffect(button);
    disableEffect->setColor(Qt::darkGray);
    disableEffect->setEnabled(false);

    button->setGraphicsEffect(disableEffect);
}

}

ViewBarButton::ViewBarButton(const QPixmap &pixmap, ViewBar *parent) : QWidget(parent)
{
    auto &c = cache.alloc<Cache>(parent, this, QString(), nullptr, pixmap);
}

ViewBarButton::ViewBarButton(const QString &text, const QPixmap &pixmap, ViewBar *parent) : QWidget(parent)
{
    auto &c = cache.alloc<Cache>(parent, this, text, nullptr, pixmap);
}

ViewBarButton::ViewBarButton(QMenu *menu, const QPixmap &pixmap, ViewBar *parent)
{
    auto &c = cache.alloc<Cache>(parent, this, QString(), menu, pixmap);
    connect(menu, SIGNAL(aboutToHide()), SLOT(reset()));
}

void ViewBarButton::setCheckable(bool state)
{
    cache.get<Cache>().checkable = state;
}

bool ViewBarButton::isCheckable() const
{
    return cache.get<Cache>().checkable;
}

bool ViewBarButton::isChecked() const
{
    return cache.get<Cache>().checked;
}

void ViewBarButton::click()
{
    emit clicked();
}

void ViewBarButton::setChecked(bool state)
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

void ViewBarButton::toggle()
{
    auto &c = cache.get<Cache>();
    if(c.checkable)
    {
        c.checked = !c.checked;
        update();

        emit toggled(c.checked);
    }
}

bool ViewBarButton::event(QEvent *event)
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

void ViewBarButton::paintEvent(QPaintEvent *event)
{
    auto &c = cache.get<Cache>();
    QPainter painter(this);

    bool down = (c.down && c.within) || c.checked;

    auto hover = qvariant_cast<QColor>(QApplication::instance()->property("ui-hover"));
    hover.setAlphaF(c.anim->currentValue().toFloat());

    painter.fillRect(rect(), down ? qvariant_cast<QColor>(QApplication::instance()->property("ui-hilight")) : hover);

    if(down)
    {
        painter.setPen(QPen(qvariant_cast<QColor>(QApplication::instance()->property("ui-border"))));
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    if(c.type == ViewBar::Type::Small)
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

        painter.setPen(qvariant_cast<QColor>(QApplication::instance()->property("ui-text")));
        painter.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, c.text);
    }
}

void ViewBarButton::reset()
{
    auto &c = cache.get<Cache>();

    c.down = false;
    c.anim->reset();
}

void ViewBarButton::buttonPressed()
{
    auto &c = cache.get<Cache>();

    c.within = c.down = true;
    update();

    if(c.menu)
    {
        c.menu->exec(mapToGlobal(QPoint(0, height())));
    }
}

void ViewBarButton::buttonReleased()
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
