#include "ToolView.h"

#include "gui/GuiLargeButton.h"
#include "gui/GuiButtonGroup.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QApplication>

ToolView::ToolView(QWidget *parent) : QWidget(parent), group(new GuiButtonGroup(this))
{
    auto layout = new QPx::VBoxLayout(this);

    QPx::setPaletteColor(this, QPalette::Window, qvariant_cast<QColor>(QApplication::instance()->property("gui-panel-color")));
    setAutoFillBackground(true);

    layout->addWidget(group->addButton(new GuiLargeButton("Select", QPixmap(":/resources/images/ark.png"))));
    layout->addWidget(group->addButton(new GuiLargeButton("Create", QPixmap(":/resources/images/ark.png"))));
    layout->addWidget(group->addButton(new GuiLargeButton("Move", QPixmap(":/resources/images/ark.png"))));

    layout->addStretch();
}
