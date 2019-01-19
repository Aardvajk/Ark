#include "GuiLargeButton.h"

#include <QtGui/QPainter>
#include <QtGui/QIcon>

#include <QtWidgets/QApplication>

GuiLargeButton::GuiLargeButton(const QString &text, const QIcon &icon, QWidget *parent) : GuiButton(parent)
{
    setFixedSize(QApplication::instance()->property("gui-tool-width").toInt(), QApplication::instance()->property("gui-tool-height").toInt());

    setText(text);
    setIcon(icon);
}

void GuiLargeButton::paintEvent(QPaintEvent *event)
{
    GuiButton::paintEvent(event);

    QPainter painter(this);

    int size = QApplication::instance()->property("gui-tool-icon-size").toInt();

    int x = (rect().width() - size) / 2;
    int y = 8;

    painter.drawPixmap(x, y, size, size, icon().pixmap(size));

    auto font = painter.font();
    font.setBold(true);
    font.setPointSize(QApplication::instance()->property("gui-tool-font-size").toInt());

    painter.setFont(font);

    QRect r(0, y + size + 2, rect().width(), QFontMetrics(font).height());

    painter.setPen(QApplication::instance()->property("gui-text-color").value<QColor>());
    painter.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, text());
}
