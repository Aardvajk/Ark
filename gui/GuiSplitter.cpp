#include "GuiSplitter.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

GuiSplitter::GuiSplitter(Qt::Orientation orientation, QWidget *parent) : QPx::LineSplitter(orientation, parent)
{
    QPx::setPaletteColor(this, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("gui-splitter")));
}
