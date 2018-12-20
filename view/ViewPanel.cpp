#include "ViewPanel.h"

#include "view/ViewBar.h"
#include "view/ViewBarButton.h"
#include "view/ViewBarButtonGroup.h"
#include "view/ViewSeparator.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

ViewPanel::ViewPanel(QWidget *parent) : SplitterPanel(parent)
{
    setPaletteColor(this, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-border")));

    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new ViewBar(Qt::Horizontal, ViewBar::Type::Small));

    auto icon = QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation);

    auto group = new ViewBarButtonGroup(bar);

    bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar)));
    bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar)));
    bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar)));

    bar->addStretch();

    auto menu = new QMenu();

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addSeparator();
    menu->addAction("Close", this, SLOT(closePanel()));

    bar->addTypedWidget(new ViewBarButton(menu, icon, bar));
}

ViewBar *ViewPanel::viewBar() const
{
    return bar;
}

void ViewPanel::splitVertical()
{
    split(Qt::Vertical, clone());
}

void ViewPanel::splitHorizontal()
{
    split(Qt::Horizontal, clone());
}

void ViewPanel::closePanel()
{
    QTimer::singleShot(0, this, SLOT(close()));
}
