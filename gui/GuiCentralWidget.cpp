#include "GuiCentralWidget.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

GuiCentralWidget::GuiCentralWidget(QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);

    QPx::setPaletteColor(this, QPalette::Window, qvariant_cast<QColor>(QApplication::instance()->property("gui-border-color")));
    setAutoFillBackground(true);
}

QPx::VBoxLayout *GuiCentralWidget::layout() const
{
    return static_cast<QPx::VBoxLayout*>(QWidget::layout());
}
