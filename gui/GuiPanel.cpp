#include "GuiPanel.h"

#include "gui/GuiBar.h"
#include "gui/GuiBarButton.h"
#include "gui/GuiBarButtonGroup.h"
#include "gui/GuiSeparator.h"
#include "gui/GuiSplitter.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

GuiPanel::GuiPanel(QWidget *parent) : SplitterPanel(parent)
{
    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new GuiBar(Qt::Horizontal, GuiBar::Type::Small));

    auto icon = QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation);

    bar->addStretch();

    auto menu = new QMenu();

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addSeparator();
    closeAction = menu->addAction("Close", this, SLOT(closePanel()));

    connect(menu, SIGNAL(aboutToShow()), SLOT(menuAboutToShow()));

    bar->addTypedWidget(new GuiBarButton(menu, icon, bar));
}

GuiBar *GuiPanel::viewBar() const
{
    return bar;
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
