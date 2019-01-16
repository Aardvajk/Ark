#include "GuiTextButton.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiTextButton::GuiTextButton(const QString &text, QWidget *parent) : GuiButton(parent), text(text)
{
    setFixedHeight(28);

    QPx::setPaletteColor(this, QPalette::Window, QApplication::instance()->property("gui-panel-color").value<QColor>());
    setAutoFillBackground(true);
}

void GuiTextButton::paintEvent(QPaintEvent *event)
{
    GuiButton::paintEvent(event);

    auto t = rect().adjusted(4, 0, -3, -1);

    QPainter painter(this);
    painter.drawText(t, Qt::AlignCenter | Qt::AlignVCenter, QFontMetrics(painter.font()).elidedText(text, Qt::ElideRight, t.width()));

    painter.setPen(QApplication::instance()->property("gui-border-color").value<QColor>());
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}
