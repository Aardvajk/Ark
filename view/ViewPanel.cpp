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

void ViewPanel::click()
{
    for(auto w: ws)
    {
        w->setEnabled(!w->isEnabled());
    }
}

ViewPanel::ViewPanel(QWidget *parent) : SplitterPanel(parent)
{
    setPaletteColor(this, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-border")));

    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new ViewBar(Qt::Horizontal, ViewBar::Type::Small));

    auto icon = QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation);

    auto group = new ViewBarButtonGroup(bar);

    ws.append(bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar))));
    ws.append(bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar))));
    bar->addTypedWidget(group->addButton(new ViewBarButton(icon, bar)));

    bar->addStretch();
    auto tb = bar->addTypedWidget(new ViewBarButton(icon, bar));
    connect(tb, SIGNAL(clicked()), SLOT(click()));

    auto button = bar->addTypedWidget(new ViewBarButton(icon, bar));
    ws.append(button);

    auto menu = button->setMenu(new QMenu(button));

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addSeparator();
    menu->addAction("Close", this, SLOT(closePanel()));
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
