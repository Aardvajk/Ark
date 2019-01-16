#include "GuiSplitter.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

GuiSplitter::GuiSplitter(Qt::Orientation orientation, QWidget *parent) : QPx::LineSplitter(orientation, parent)
{
    QPx::setPaletteColor(this, QPalette::Background, QApplication::instance()->property("gui-border-color").value<QColor>());
}
