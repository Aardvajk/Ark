#include "ActionList.h"

#include <QPxCore/QPxAction.h>
#include <QPxCore/QPxSettings.h>

#include <QtGui/QKeySequence>

ActionList::ActionList(QPx::Settings &settings, QWidget *parent) : QPx::ActionList(parent), settings(settings)
{
}

QPx::Action *ActionList::add(const QString &id, const QString &text, const QKeySequence &shortcut, const QIcon &icon, ActionList::Enable enable)
{
    return QPx::ActionList::add(id, text, QKeySequence(settings[id]["Shortcut"].value<QString>(shortcut.toString(QKeySequence::NativeText))), icon, enable);
}

QPx::Action *ActionList::add(const QString &id, const QString &text, const QKeySequence &shortcut, ActionList::Enable enable)
{
    return add(id, text, shortcut, QIcon(), enable);
}

QPx::Action *ActionList::add(const QString &id, const QString &text, ActionList::Enable enable)
{
    return add(id, text, QKeySequence(), QIcon(), enable);
}

QPx::Action *ActionList::addCheckable(const QString &id, const QString &text, bool state, QPx::ActionList::Enable enable)
{
    auto a = add(id, text, enable);

    a->setCheckable(true);
    a->setChecked(settings[id]["Checked"].value<bool>(state));

    return a;
}

void ActionList::sync()
{
    settings.clear();

    for(auto a: toList())
    {
        settings[a->id()]["Shortcut"].setValue(a->shortcut().toString(QKeySequence::NativeText));

        if(a->isCheckable())
        {
            settings[a->id()]["Checked"].setValue(a->isChecked());
        }
    }
}
