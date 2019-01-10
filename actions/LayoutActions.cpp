#include "LayoutActions.h"

#include "actions/ActionList.h"

#include "MainWindow.h"

#include <QPxActions/QPxAction.h>

#include <QtWidgets/QLayout>
#include <QtWidgets/QSplitter>

LayoutActions::LayoutActions(ActionList *actions, MainWindow *parent) : QObject(parent), actions(actions)
{
    auto layout = parent->centralWidget()->layout()->itemAt(1)->layout();

    connect(actions->addCheckable("Layout.Left.Tools", "Left Tools", true), SIGNAL(toggled(bool)), layout->itemAt(0)->widget(), SLOT(setVisible(bool)));
    connect(actions->addCheckable("Layout.Right.Tools", "Right Tools", true), SIGNAL(toggled(bool)), layout->itemAt(2)->widget(), SLOT(setVisible(bool)));

    auto splitter = static_cast<QSplitter*>(layout->itemAt(1)->widget());

    connect(actions->addCheckable("Layout.Left.Sidebar", "Left Sidebar", true), SIGNAL(toggled(bool)), splitter->widget(0), SLOT(setVisible(bool)));
    connect(actions->addCheckable("Layout.Right.Sidebar", "Right Sidebar", true), SIGNAL(toggled(bool)), splitter->widget(2), SLOT(setVisible(bool)));

    layout->itemAt(0)->widget()->setVisible(actions->find("Layout.Left.Tools")->isChecked());
    layout->itemAt(2)->widget()->setVisible(actions->find("Layout.Right.Tools")->isChecked());

    splitter->widget(0)->setVisible(actions->find("Layout.Left.Sidebar")->isChecked());
    splitter->widget(2)->setVisible(actions->find("Layout.Right.Sidebar")->isChecked());
}
