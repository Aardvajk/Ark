#ifndef MARQUEE_H
#define MARQUEE_H

#include <GxMaths/GxSize.h>
#include <GxMaths/GxVector.h>

class QMouseEvent;
class QRectF;
class QWidget;

class Marquee
{
public:
    Marquee();

    void begin(QWidget *widget, QMouseEvent *event);
    void update(QMouseEvent *event);
    void end();

    Gx::Vec2 anchor() const;
    Gx::Vec2 position() const;

    QRectF clipRect(const Gx::SizeF &size) const;

    QWidget *widget() const;
    bool valid() const;

private:
    QWidget *w;

    Gx::Vec2 anc;
    Gx::Vec2 pos;
};

#endif // MARQUEE_H
