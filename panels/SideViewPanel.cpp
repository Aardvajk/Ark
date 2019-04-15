#include "SideViewPanel.h"

#include "core/Relay.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiComboBox.h"

#include "views/PropertyView.h"
#include "views/ToolOptionsView.h"
#include "views/ResourcesView.h"

#include "models/PropertyModel.h"

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxPalette.h>
#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QMenu>

SideViewPanel::SideViewPanel(Model *model, Relay *relay, PropertyTypeFactory *factory, Tool *tool, QWidget *parent) : GuiPanel(parent), model(model), relay(relay), factory(factory), currentTool(tool)
{
    combo = toolBar()->addTypedWidget(new GuiComboBox());
    combo->addItem("Model");
    combo->addItem("Objects");
    combo->addItem("Faces");
    combo->addItem("Vertices");
    combo->addItem("Tools");
    combo->addItem("Resources");

    auto menu = new QMenu(this);

    for(int i = 0; i < combo->count(); ++i)
    {
        auto a = menu->addAction(QIcon(":/resources/images/splitvert.png"), combo->itemText(i), this, SLOT(splitMenuSelected()));
        a->setProperty("ark-combo-index", i);
    }

    menu->addSeparator();
    menu->addAction(maximizeAction());
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = setPanelButton(toolBar()->addTypedWidget(new GuiSmallButton(QIcon(":/resources/images/splitvert.png"))));
    button->setMenu(menu);

    panelLayout = new QPx::VBoxLayout(layout()->addTypedWidget(new QWidget()));

    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(comboIndexChanged(int)));
    connect(relay, SIGNAL(toolSelected(Tool*)), SLOT(toolSelected(Tool*)));

    comboIndexChanged(0);
}

void SideViewPanel::saveState(QPx::Settings &settings) const
{
    settings["index"].setValue(combo->currentIndex());
}

void SideViewPanel::restoreState(const QPx::Settings &settings)
{
    combo->setCurrentIndex(settings["index"].value<int>());
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

    QWidget *view = nullptr;
    switch(index)
    {
        case 0: view = new PropertyView(new PropertyModel(Element::Type::Model, model, factory), this); break;
        case 1: view = new PropertyView(new PropertyModel(Element::Type::Object, model, factory), this); break;
        case 2: view = new PropertyView(new PropertyModel(Element::Type::Face, model, factory), this); break;
        case 3: view = new PropertyView(new PropertyModel(Element::Type::Vertex, model, factory), this); break;
        case 4: view = new ToolOptionsView(relay, currentTool, this); break;
        case 5: view = new ResourcesView(model, this); break;
    }

    if(view) panelLayout->addWidget(view);
}

void SideViewPanel::splitMenuSelected()
{
    auto c = clone();
    split(Qt::Vertical, c);

    c->combo->setCurrentIndex(sender()->property("ark-combo-index").toInt());
}
