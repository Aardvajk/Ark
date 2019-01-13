#ifndef MARQUEE_H
#define MARQUEE_H

#include <GxMaths/GxSize.h>
#include <GxMaths/GxVector.h>

class QWidget;
class QMouseEvent;
class QRectF;

class Marquee
{
public:
    Marquee();

    void begin(QWidget *widget, QMouseEvent *event);
    void update(QWidget *widget, QMouseEvent *event);
    void end(QWidget *widget);

    Gx::Vec2 anchor() const;
    Gx::Vec2 position() const;

    QRectF clipRect(const Gx::SizeF &size) const;

    QWidget *widget() const;

    bool active(QWidget *widget) const;
    bool valid(QWidget *widget) const;

private:
    QWidget *wgt;

    Gx::Vec2 anc;
    Gx::Vec2 pos;
};

#endif // MARQUEE_H
