#include "ViewSplitter.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

ViewSplitter::ViewSplitter(Qt::Orientation orientation, QWidget *parent) : QPx::LineSplitter(orientation, parent)
{
    QPx::setPaletteColor(this, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-border")));
}
