#include "GuiSeparator.h"

#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

GuiSeparator::GuiSeparator(Qt::Orientation orientation, QWidget *parent) : QWidget(parent)
{
    QPx::setPaletteColor(this, QPalette::Window, qvariant_cast<QColor>(QApplication::instance()->property("gui-splitter")));
    setAutoFillBackground(true);

    if(orientation == Qt::Vertical)
    {
        setFixedWidth(1);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
    else
    {
        setFixedHeight(1);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
}
