#include "Marquee.h"

#include <QtGui/QMouseEvent>

Marquee::Marquee() : wgt(nullptr)
{
}

void Marquee::begin(QWidget *widget, QMouseEvent *event)
{
    wgt = widget;
    anc = pos = Gx::Vec2(event->pos().x(), event->pos().y());
}

void Marquee::update(QWidget *widget, QMouseEvent *event)
{
    if(active(widget))
    {
        pos = Gx::Vec2(event->pos().x(), event->pos().y());
    }
}

void Marquee::end(QWidget *widget)
{
    if(wgt == widget)
    {
        wgt = nullptr;
    }
}

Gx::Vec2 Marquee::anchor() const
{
    return anc;
}

Gx::Vec2 Marquee::position() const
{
    return pos;
}

QRectF Marquee::clipRect(const Gx::SizeF &size) const
{
    float xa = anc.x;
    float ya = anc.y;

    float xb = pos.x;
    float yb = pos.y;

    if(xa > xb) std::swap(xa, xb);
    if(ya > yb) std::swap(ya, yb);

    const float dot = 1.0f;

    if(xa == xb)
    {
        xa -= dot;
        xb += dot;
    }

    if(ya == yb)
    {
        ya -= dot;
        yb += dot;
    }

    float hx = size.width / 2.0f;
    float hy = size.height / 2.0f;

    QRectF r;

    r.setTopLeft(QPointF((xa - hx) / hx, -(ya -hy) / hy));
    r.setBottomRight(QPointF((xb - hx) / hx, -(yb -hy) / hy));

    return r;
}

QWidget *Marquee::widget() const
{
    return wgt;
}

bool Marquee::active(QWidget *widget) const
{
    return wgt == widget;
}

bool Marquee::valid(QWidget *widget) const
{
    return wgt == widget && Gx::Vec2(anc - pos).length() >= 4.0f;
}
