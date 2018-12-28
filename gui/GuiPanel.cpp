#include "GuiPanel.h"

#include "gui/GuiSplitter.h"
#include "gui/GuiBar.h"
#include "gui/GuiBarButton.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

GuiPanel::GuiPanel(QWidget *parent) : SplitterPanel(parent)
{
    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new GuiBar());

    bar->addStretch();
    auto button = bar->addTypedWidget(new GuiBarButton(QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation)));

    auto menu = button->setMenu(new QMenu(button));

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addSeparator();
    closeAction = menu->addAction("Close", this, SLOT(closePanel()));

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));
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
