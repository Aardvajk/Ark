#include "GuiPanel.h"

#include "gui/GuiSplitter.h"
#include "gui/GuiBar.h"
#include "gui/GuiBarButton.h"
#include "gui/GuiSeparator.h"

#include <QPxWidgets/QPxLayouts.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>

GuiPanel::GuiPanel(QWidget *parent) : SplitterPanel(parent), close(new QAction("Close", this))
{
    auto layout = new QPx::VBoxLayout(this);

    bar = layout->addTypedWidget(new GuiBar());
    layout->addWidget(new GuiSeparator(Qt::Horizontal));

    connect(close, SIGNAL(triggered()), SLOT(closePanel()));
}

GuiBar *GuiPanel::toolBar() const
{
    return bar;
}

QAction *GuiPanel::closeAction() const
{
    return close;
}

QSplitter *GuiPanel::createSplitter(Qt::Orientation orientation) const
{
    return new GuiSplitter(orientation);
}

void GuiPanel::menuAboutToShow()
{
    close->setVisible(qobject_cast<QSplitter*>(parentWidget()));
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
