#include "SideViewPanel.h"

#include "core/Relay.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiComboBox.h"

#include "views/PropertyView.h"
#include "views/ToolOptionsView.h"

#include "models/PropertyModel.h"

#include <QPxWidgets/QPxPalette.h>
#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QMenu>

SideViewPanel::SideViewPanel(Model *model, Relay *relay, PropertyTypeFactory *factory, Tool *tool, QWidget *parent) : GuiPanel(parent), model(model), relay(relay), factory(factory), currentTool(tool)
{
    auto combo = toolBar()->addTypedWidget(new GuiComboBox());
    combo->addItem("Model");
    combo->addItem("Objects");
    combo->addItem("Faces");
    combo->addItem("Tools");

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split", this, SLOT(splitVertical()));
    menu->addSeparator();
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = toolBar()->addTypedWidget(new GuiSmallButton(QPixmap(":/resources/images/splitvert.png")));
    button->setMenu(menu);

    panelLayout = new QPx::VBoxLayout(layout()->addTypedWidget(new QWidget()));

    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(comboIndexChanged(int)));
    connect(relay, SIGNAL(toolSelected(Tool*)), SLOT(toolSelected(Tool*)));

    comboIndexChanged(0);
}

void SideViewPanel::saveState(QPx::Settings &settings) const
{
}

void SideViewPanel::restoreState(const QPx::Settings &settings)
{
}

SideViewPanel *SideViewPanel::clone() const
{
    return new SideViewPanel(model, relay, factory, currentTool);
}

void SideViewPanel::toolSelected(Tool *tool)
{
    currentTool = tool;
}

void SideViewPanel::comboIndexChanged(int index)
{
    panelLayout->clear();

    switch(index)
    {
        case 0: panelLayout->addWidget(new PropertyView(new PropertyModel(Element::Type::Model, model, factory))); break;
        case 1: panelLayout->addWidget(new PropertyView(new PropertyModel(Element::Type::Object, model, factory))); break;
        case 2: panelLayout->addWidget(new PropertyView(new PropertyModel(Element::Type::Face, model, factory))); break;
        case 3: panelLayout->addWidget(new ToolOptionsView(relay, currentTool)); break;
    }
}
