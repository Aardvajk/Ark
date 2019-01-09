#include "SideViewPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiSmallButton.h"
#include "gui/GuiComboBox.h"

#include <QtWidgets/QTreeView>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMenu>

SideViewPanel::SideViewPanel(QWidget *parent) : GuiPanel(parent)
{
    auto view = new QTreeView();
    view->setFrameStyle(QFrame::NoFrame);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    layout()->addWidget(view);

    auto cb = toolBar()->addTypedWidget(new GuiComboBox());
    cb->addItem("Model");
    cb->addItem("Selection");
    cb->addItem("Elements");

    auto menu = new QMenu(this);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split", this, SLOT(splitVertical()));
    menu->addSeparator();
    menu->addAction(closeAction());

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = toolBar()->addTypedWidget(new GuiSmallButton(QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation)));
    button->setMenu(menu);
}

void SideViewPanel::saveState(QPx::Settings &settings) const
{
}

void SideViewPanel::restoreState(const QPx::Settings &settings)
{
}

SideViewPanel *SideViewPanel::clone() const
{
    return new SideViewPanel();
}
