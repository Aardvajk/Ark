#include "GuiPopupWindow.h"

#include <QPxCore/QPxUnitAnimation.h>

GuiPopupWindow::GuiPopupWindow(QWidget *widget, QWidget *parent) : QWidget(parent, Qt::Popup), w(widget), anim(new QPx::UnitAnimation(200, this))
{
    if(w)
    {
        w->setParent(this);
    }

    setVisible(false);

    connect(anim, SIGNAL(currentValueChanged(float)), SLOT(animChanged(float)));
}

void GuiPopupWindow::fadeIn(QWidget *widget)
{
    if(widget)
    {
        move(widget->mapToGlobal(QPoint(0, widget->height() - 1)));
        show();
    }
}

void GuiPopupWindow::showEvent(QShowEvent *event)
{
    setWindowOpacity(0);

    if(w)
    {
        w->move(0, 0);
        resize(w->sizeHint());
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
    setWindowOpacity(value);
}
