#include "ToolOptionsView.h"

#include "core/Relay.h"

#include "tools/Tool.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtWidgets/QGroupBox>

#include <QtWidgets/QPushButton>

ToolOptionsView::ToolOptionsView(Relay *relay, QWidget *parent) : QScrollArea(parent)
{
    setWidgetResizable(true);
    setFrameStyle(QFrame::NoFrame);

    auto container = new QWidget();
    QPx::setPaletteColor(container, QPalette::Window, Qt::white);

    setWidget(container);

    auto layout = new QPx::VBoxLayout({ }, { }, container);

    groupBox = layout->addTypedWidget(new QGroupBox("None"));
    groupLayout = new QPx::VBoxLayout({ }, { }, groupBox);

    connect(relay, SIGNAL(toolSelected(Tool*)), SLOT(toolChanged(Tool*)));
}

void ToolOptionsView::toolChanged(Tool *tool)
{
    groupLayout->clear();

    if(tool)
    {
        groupBox->setTitle(tool->name());

        tool->addOptions(groupLayout);
        groupLayout->addStretch();
    }
}
