#include "GuiSeparator.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiSeparator::GuiSeparator(Style style, Qt::Orientation orientation, QWidget *parent) : QWidget(parent), style(style)
{
    if(orientation == Qt::Vertical)
    {
        setFixedWidth(style == Style::Line ? 1 : 16);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
    else
    {
        setFixedHeight(style == Style::Line ? 1 : 16);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
}

void GuiSeparator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    auto color = QApplication::instance()->property("gui-border-color").value<QColor>();

    if(style == Style::Line)
    {
        painter.fillRect(rect(), color);
    }
    else
    {
        int y = rect().height() / 2;

        painter.setPen(color);
        painter.drawLine(0, y, rect().width(), y);

        painter.setPen(QApplication::instance()->property("gui-hilight-color").value<QColor>());
        painter.drawLine(0, y + 1, rect().width(), y + 1);
    }
}
