#include "GuiLayoutWidget.h"

#include <QtWidgets/QApplication>

GuiLayoutWidget::GuiLayoutWidget(QLayout *layout, QWidget *parent) : QWidget(parent)
{
    setLayout(layout);

    auto p = palette();
    p.setColor(QPalette::Window, Qt::red);

    setPalette(p);
    setAutoFillBackground(true);
}
