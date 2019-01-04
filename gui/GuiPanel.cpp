#include "GuiPanel.h"

#include "gui/GuiSplitter.h"
#include "gui/GuiBar.h"
#include "gui/GuiBarButton.h"
#include "gui/GuiSeparator.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

GuiPanel::GuiPanel(QWidget *parent) : SplitterPanel(parent), menu(nullptr), closeAction(nullptr)
{
    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new GuiBar());
    layout->addWidget(new GuiSeparator(Qt::Horizontal));
}

GuiBar *GuiPanel::toolBar() const
{
    return bar;
}

void GuiPanel::addSplitButton(SplitType type)
{
    menu = new QMenu(this);

    if(type == SplitType::Vertical || type == SplitType::Both)
    {
        menu->addAction(QIcon(":/resources/images/splitvert.png"), type == SplitType::Vertical ? "Split" : "Split Vertical", this, SLOT(splitVertical()));
    }

    if(type == SplitType::Horizontal || type == SplitType::Both)
    {
        menu->addAction(QIcon(":/resources/images/splithorz.png"), type == SplitType::Horizontal ? "Split" : "Split Horizontal", this, SLOT(splitHorizontal()));
    }

    menu->addSeparator();
    closeAction = menu->addAction("Close", this, SLOT(closePanel()));

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    auto button = bar->addTypedWidget(new GuiBarButton(QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation)));
    button->setMenu(menu);
}

QSplitter *GuiPanel::createSplitter(Qt::Orientation orientation) const
{
    return new GuiSplitter(orientation);
}

void GuiPanel::menuAboutToShow()
{
    closeAction->setVisible(qobject_cast<QSplitter*>(parentWidget()));
}

void GuiPanel::splitVertical()
{
    split(Qt::Vertical, clone());
}

void GuiPanel::splitHorizontal()
{
    split(Qt::Horizontal, clone());
}

void GuiPanel::closePanel()
{
    QTimer::singleShot(0, this, SLOT(close()));
}
