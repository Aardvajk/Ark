#include "ActionList.h"

#include <QPxCore/QPxSettings.h>

#include <QPxActions/QPxAction.h>

#include <QtGui/QKeySequence>

ActionList::ActionList(QPx::Settings &settings, QWidget *parent) : QPx::ActionList(parent), settings(settings)
{
}

QPx::Action *ActionList::add(const QString &id, const QString &text, const QKeySequence &shortcut, const QIcon &icon, ActionList::Enable enable)
{
    return QPx::ActionList::add(id, text, QKeySequence(settings[id]["Shortcut"].value(shortcut.toString(QKeySequence::NativeText)).toString()), icon, enable);
}

QPx::Action *ActionList::add(const QString &id, const QString &text, ActionList::Enable enable)
{
    return add(id, text, QKeySequence(), QIcon(), enable);
}

void ActionList::sync()
{
    for(auto a: toList())
    {
        settings[a->id()]["Shortcut"].setValue(a->shortcut().toString(QKeySequence::NativeText));
    }
}
