#include "ToolOptionsPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiSeparator.h"

#include <QPxWidgets/QPxLayouts.h>

ToolOptionsPanel::ToolOptionsPanel(QWidget *parent) : QWidget(parent)
{
    new QPx::VBoxLayout(this);

    layout()->addWidget(new GuiBar(this));
    layout()->addWidget(new GuiSeparator(Qt::Horizontal));

    auto w = new QWidget();
    w->setBackgroundRole(QPalette::Base);
    w->setAutoFillBackground(true);

    layout()->addWidget(w);
}
