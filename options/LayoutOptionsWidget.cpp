#include "LayoutOptionsWidget.h"

#include "options/components/LayoutDiagram.h"

#include <QPxWidgets/QPxLayouts.h>

LayoutOptionsWidget::LayoutOptionsWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QPx::VBoxLayout(16, 0, this);
    layout->addWidget(new LayoutDiagram());
}
