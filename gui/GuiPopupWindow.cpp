#include "GuiPopupWindow.h"

#include <QPxCore/QPxUnitAnimation.h>


namespace
{

float interpolate(float a, float b, float t)
{
    return (b * t) + (a * (1.0f - t));
}

QSize interpolate(const QSize &a, const QSize &b, float t)
{
    float w = interpolate(static_cast<float>(a.width()), static_cast<float>(b.width()), t);
    float h = interpolate(static_cast<float>(a.height()), static_cast<float>(b.height()), t);

    return QSize(static_cast<int>(w), static_cast<int>(h));
}

}

GuiPopupWindow::GuiPopupWindow(QWidget *widget, QWidget *parent) : QFrame(parent, Qt::Popup), w(widget), anim(new QPx::UnitAnimation(400, this))
{
    setFrameStyle(QFrame::StyledPanel);

    if(w)
    {
        w->setParent(this);
        w->move(0, 0);
    }

    setVisible(false);

    connect(anim, SIGNAL(currentValueChanged(float)), SLOT(animChanged(float)));
}

void GuiPopupWindow::unfold()
{
    if(auto s = dynamic_cast<QWidget*>(sender()))
    {
        move(s->mapToGlobal(QPoint(0, s->height() - 1)));

        ss = QSize(s->width(), 0);
        ts = w->sizeHint();

        show();
    }
}

void GuiPopupWindow::showEvent(QShowEvent *event)
{
    resize(ss);

    if(w)
    {
        w->resize(ts);
    }

    anim->reset();
    anim->start();
}

void GuiPopupWindow::hideEvent(QHideEvent *event)
{
    emit hidden();
}

void GuiPopupWindow::animChanged(float value)
{
    resize(interpolate(ss, ts, value));

    if(w)
    {
        w->move(-(ts.width() - width()), -(ts.height() - height()));
    }
}
