#include "GuiSmallButton.h"

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiSmallButton::GuiSmallButton(const QIcon &icon, QWidget *parent) : GuiButton(parent)
{
    int size = QApplication::instance()->property("gui-bar-height").toInt();
    setFixedSize(size, size);

    setIcon(icon);
}

void GuiSmallButton::paintEvent(QPaintEvent *event)
{
    GuiButton::paintEvent(event);

    QPainter painter(this);

    int size = QApplication::instance()->property("gui-bar-icon-size").toInt();

    int x = (rect().width() - size) / 2;
    int y = (rect().height() - size) / 2;

    painter.drawPixmap(x, y, size, size, icon().pixmap(size));
}
