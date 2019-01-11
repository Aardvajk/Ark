#include "GuiLargeButton.h"

#include <QtGui/QPainter>

#include <QtWidgets/QApplication>

GuiLargeButton::GuiLargeButton(const QString &text, const QPixmap &pixmap, QWidget *parent) : GuiButton(parent), text(text), pixmap(pixmap)
{
    setFixedSize(QApplication::instance()->property("gui-tool-width").toInt(), QApplication::instance()->property("gui-tool-height").toInt());
}

void GuiLargeButton::paintEvent(QPaintEvent *event)
{
    GuiButton::paintEvent(event);

    QPainter painter(this);

    int size = QApplication::instance()->property("gui-tool-icon-size").toInt();

    int x = (rect().width() - size) / 2;
    int y = 8;

    painter.drawPixmap(x, y, size, size, pixmap);

    auto font = painter.font();
    font.setBold(true);
    font.setPointSize(QApplication::instance()->property("gui-tool-font-size").toInt());

    painter.setFont(font);

    QRect r(0, y + size + 2, rect().width(), QFontMetrics(font).height());

    painter.setPen(qvariant_cast<QColor>(QApplication::instance()->property("gui-text-color")));
    painter.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, text);
}
