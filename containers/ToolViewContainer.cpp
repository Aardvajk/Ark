#include "ToolViewContainer.h"

#include "views/ToolView.h"

#include "gui/GuiBar.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QApplication>

ToolViewContainer::ToolViewContainer(QWidget *parent) : GuiLayoutWidget(new QPx::VBoxLayout(0, 1), parent)
{
    setFixedWidth(QApplication::instance()->property("gui-tool-width").toInt());

    layout()->addWidget(new GuiBar());
    layout()->addWidget(new ToolView());
}
