#include "ViewPanel.h"

#include "gui/ViewBar.h"
#include "gui/ViewBarButton.h"
#include "gui/LineSeparator.h"

#include <QPxWidgets/QPxLayouts.h>
#include <QPxWidgets/QPxPalette.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

ViewPanel::ViewPanel(QWidget *parent) : QPx::SplitterPanel(parent)
{
    QPx::setPaletteColor(this, QPalette::Background, qvariant_cast<QColor>(QApplication::instance()->property("ui-dark")));

    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new ViewBar(Qt::Horizontal, ViewBar::Type::Small));
    layout->addWidget(new LineSeparator(Qt::Horizontal));

    bar->addStretch();
    auto button = bar->addTypedWidget(new ViewBarButton(QPixmap(":/resources/images/ark.png").scaledToHeight(16, Qt::SmoothTransformation), bar));

    auto menu = new QMenu(button);
    button->setMenu(menu);

    menu->addAction(QIcon(":/resources/images/splitvert.png"), "Split Vertical", this, SLOT(splitVertical()));
    menu->addAction(QIcon(":/resources/images/splithorz.png"), "Split Horizontal", this, SLOT(splitHorizontal()));
    menu->addSeparator();
    menu->addAction("Close", this, SLOT(closeWindow()));
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

void ViewPanel::closeWindow()
{
    QTimer::singleShot(0, this, SLOT(close()));
}
