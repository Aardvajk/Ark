#include "GuiBar.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiBar::GuiBar(QWidget *parent) : QWidget(parent)
{
    new QPx::HBoxLayout(this);
    setFixedHeight(QApplication::instance()->property("gui-bar-height").toInt());
}

void GuiBar::addWidget(QWidget *widget)
{
    layout()->addWidget(widget);
}

void GuiBar::addStretch()
{
    static_cast<QBoxLayout*>(layout())->addStretch();
}

void GuiBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), qvariant_cast<QColor>(QApplication::instance()->property("gui-panel-color")));
}
