#include "ApplicationActions.h"

#include "MainWindow.h"

#include "actions/ActionList.h"

#include "options/OptionsDialog.h"

ApplicationActions::ApplicationActions(ActionList *actions, MainWindow *parent) : QObject(parent), actions(actions), parent(parent)
{
    connect(actions->add("Application.Options", "&Options..."), SIGNAL(triggered()), SLOT(showOptions()));
    connect(actions->add("Application.Exit", "E&xit"), SIGNAL(triggered()), parent, SLOT(close()));
}

void ApplicationActions::showOptions()
{
    OptionsDialog dialog(actions, parent);
    dialog.exec();
}
