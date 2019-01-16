#include "SideViewPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiComboBox.h"

#include "views/ToolOptionsView.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtWidgets/QMenu>

#include <QPxWidgets/QPxPalette.h>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include "gui/GuiTextButton.h"
#include "gui/GuiButtonGroup.h"
#include "controls/SettingsCheckBox.h"

GuiTextButton *bb(const QString &text)
{
    auto t = new GuiTextButton(text);
    t->setCheckable(true);
    return t;
}

SideViewPanel::SideViewPanel(Relay *relay, QWidget *parent) : GuiPanel(parent), relay(relay)
{
    auto combo = toolBar()->addTypedWidget(new GuiComboBox());
    combo->addItem("Tools");
    combo->addItem("Properties");

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split", this, SLOT(splitVertical()));
    menu->addSeparator();
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = toolBar()->addTypedWidget(new GuiSmallButton(QPixmap(":/resources/images/splitvert.png")));
    button->setMenu(menu);

    auto stack = layout()->addTypedLayout(new QPx::StackedLayout());

    stack->addWidget(new ToolOptionsView(relay));

//auto w = new QWidget();
//QPx::setPaletteColor(w, QPalette::Window, Qt::white);
//auto wl = new QPx::VBoxLayout({ }, { }, w);

//auto gb = wl->addTypedWidget(new QGroupBox("Select"));
//auto gl = new QPx::VBoxLayout({ }, { }, gb);

//auto bl = gl->addTypedLayout(new QPx::HBoxLayout({ }, 2));

//bl->addWidget(bb("Object"));
//bl->addWidget(bb("Face"));
//bl->addWidget(bb("Vertex"));
//bl->addWidget(bb("Group"));

//gl->addWidget(new QCheckBox("Front Faces Only"));
//gl->addStretch();

//auto sa = stack->addTypedWidget(new QScrollArea());
//sa->setFrameStyle(QFrame::NoFrame);
//sa->setWidget(w);
//sa->setWidgetResizable(true);

auto t = stack->addTypedWidget(new QTreeWidget());
t->setFrameStyle(QFrame::NoFrame);
auto item = new QTreeWidgetItem(QStringList() << "Top");
t->addTopLevelItem(item);
for(int i = 0; i < 100; ++i)
{
    item->addChild(new QTreeWidgetItem(QStringList() << "Item"));
}

    connect(combo, SIGNAL(currentIndexChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

void SideViewPanel::saveState(QPx::Settings &settings) const
{
}

void SideViewPanel::restoreState(const QPx::Settings &settings)
{
}

SideViewPanel *SideViewPanel::clone() const
{
    return new SideViewPanel(relay);
}
