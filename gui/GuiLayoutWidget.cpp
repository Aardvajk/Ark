#include "GuiLayoutWidget.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

GuiLayoutWidget::GuiLayoutWidget(QLayout *layout, QWidget *parent) : QWidget(parent)
{
    QPx::setPaletteColor(this, QPalette::Window, qvariant_cast<QColor>(QApplication::instance()->property("gui-border-color")));
    setAutoFillBackground(true);

    setLayout(layout);
}
