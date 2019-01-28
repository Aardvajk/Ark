#include "FileActions.h"

#include "actions/ActionList.h"

#include "models/Model.h"

#include <QPxCore/QPxAction.h>

FileActions::FileActions(Model *model, ActionList *actions, QWidget *parent) : QPx::EditorFileActions(model, parent)
{
    connect(actions->add("File.New", "&New", { }, QIcon(":/resources/images/new.png")), SIGNAL(triggered()), SLOT(clear()));
    connect(actions->add("File.Open", "&Open...", QKeySequence("Ctrl+O"), QIcon(":/resources/images/open.png")), SIGNAL(triggered()), SLOT(open()));
    connect(actions->add("File.Save", "&Save", QKeySequence("Ctrl+S"), QIcon(":/resources/images/save.png")), SIGNAL(triggered()), SLOT(save()));
    connect(actions->add("File.Save.As", "Save &As..."), SIGNAL(triggered()), SLOT(saveAs()));
}
