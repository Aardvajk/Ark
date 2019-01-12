#include "ToolViewContainer.h"

#include "views/ToolView.h"

#include "gui/GuiBar.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QApplication>

ToolViewContainer::ToolViewContainer(Relay *relay, QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(0, 1, this);

    setFixedWidth(QApplication::instance()->property("gui-tool-width").toInt());

    layout()->addWidget(new GuiBar());
    layout()->addWidget(new ToolView(relay));
}
