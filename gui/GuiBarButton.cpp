#include "GuiBarButton.h"

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiBarButton::GuiBarButton(const QPixmap &pixmap, QWidget *parent) : GuiButton(parent), pixmap(pixmap)
{
    int size = QApplication::instance()->property("gui-bar-height").toInt();
    setFixedSize(size, size);
}

void GuiBarButton::paintEvent(QPaintEvent *event)
{
    GuiButton::paintEvent(event);

    QPainter painter(this);

    int size = QApplication::instance()->property("gui-bar-icon-size").toInt();

    int x = (rect().width() - size) / 2;
    int y = (rect().height() - size) / 2;

    painter.drawPixmap(x, y, size, size, pixmap);
}
