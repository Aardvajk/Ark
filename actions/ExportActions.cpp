#include "ExportActions.h"

#include "models/Model.h"

#include "actions/ActionList.h"

#include "commands/ModifyPropertyCommand.h"

#include "export/Export.h"

#include <QPxCore/QPxAction.h>

#include <QtCore/QStandardPaths>

#include <QtGui/QIcon>
#include <QtGui/QKeySequence>

#include <QtWidgets/QFileDialog>

namespace
{

QString pathDialog(QWidget *widget, const Model *model)
{
    auto path = model->property("Export").value<QString>();
    if(path.isEmpty())
    {
        path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }

    return QFileDialog::getSaveFileName(widget, "Export", path, "*.*", 0);
}

}

ExportActions::ExportActions(Model *model, ActionList *actions, QWidget *parent) : QObject(parent), widget(parent), model(model)
{
    actions->add("Export.Save", "&Export", QPx::ActionList::Enable::On);
    actions->add("Export.Save.As", "Export As...", QPx::ActionList::Enable::On);

    connect(actions->find("Export.Save"), SIGNAL(triggered()), SLOT(save()));
    connect(actions->find("Export.Save.As"), SIGNAL(triggered()), SLOT(saveAs()));
}

void ExportActions::save()
{
    auto path = model->property("Export").value<QString>();
    if(path.isEmpty())
    {
        saveAs();
        return;
    }

    exportModel(path, model);
}

void ExportActions::saveAs()
{
    auto path = pathDialog(widget, model);
    if(path.isEmpty())
    {
        return;
    }

    if(exportModel(path, model) && path != model->property("Export").value<QString>())
    {
        auto command = new ModifyPropertyCommand("Export Path", model);
        command->change(Element::Type::None, "Export", -1, -1, path);

        model->endCommand(command);
    }
}
