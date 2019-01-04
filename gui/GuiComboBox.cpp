#include "GuiComboBox.h"

#include <QPxCore/QPxAnimations.h>

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

namespace
{

class Cache
{
public:
    Cache(QObject *parent) : open(false), anim(new QPx::UnitAnimation(300, 600, parent)) { }

    bool open;
    QPx::UnitAnimation *anim;
};

void drawArrow(QPainter &painter, const QRect &rect, const QColor &color)
{
    int x = rect.x() + ((rect.width() - 7) / 2);
    int y = rect.y() + ((rect.height() - 4) / 2);

    painter.setPen(color);

    for(int i = 0; i < 4; ++i)
    {
        painter.drawLine(x + i, y + i, x + (6 - i), y + i);
    }
}

}

GuiComboBox::GuiComboBox(QWidget *parent) : QComboBox(parent)
{
    auto &c = cache.alloc<Cache>(this);

    setAttribute(Qt::WA_Hover);

    setFixedHeight(QApplication::instance()->property("gui-bar-height").toInt());
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    setMinimumWidth(QApplication::instance()->property("gui-bar-icon-size").toInt());

    connect(c.anim, SIGNAL(valueChanged(QVariant)), SLOT(update()));
}

void GuiComboBox::showPopup()
{
    cache.get<Cache>().open = true;
    update();

    QComboBox::showPopup();
}

void GuiComboBox::hidePopup()
{
    auto &c = cache.get<Cache>();

    QComboBox::hidePopup();

    c.open = false;
    c.anim->reset();

    update();
}

void GuiComboBox::paintEvent(QPaintEvent *event)
{
    auto &c = cache.get<Cache>();

    QPainter painter(this);

    int size = QApplication::instance()->property("gui-bar-icon-size").toInt();

    auto hover = qvariant_cast<QColor>(QApplication::instance()->property("gui-hover-color"));
    hover.setAlphaF(c.anim->currentValue().toFloat());

    auto text = qvariant_cast<QColor>(QApplication::instance()->property("gui-text-color"));
    auto hilight = qvariant_cast<QColor>(QApplication::instance()->property("gui-hilight-color"));

    painter.fillRect(rect(), c.open ? hilight : hover);

    auto rc = rect().adjusted(4, 0, -size, 0);

    painter.setPen(text);

    QFontMetrics fm(painter.font());
    painter.drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, fm.elidedText(currentText(), Qt::ElideMiddle, rc.width()));

    drawArrow(painter, rect().adjusted(rect().width() - size, 1, 0, 1), hilight);
    drawArrow(painter, rect().adjusted(rect().width() - size, 0, 0, 0), text);
}

bool GuiComboBox::event(QEvent *event)
{
    auto &c = cache.get<Cache>();

    switch(event->type())
    {
        case QEvent::HoverEnter: c.anim->activate(); break;
        case QEvent::HoverLeave: c.anim->deactivate(); break;

        default: break;
    }

    return QComboBox::event(event);
}
