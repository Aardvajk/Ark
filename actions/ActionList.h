#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <QPxCore/QPxActionList.h>
#include <QPxCore/QPxAction.h>

namespace QPx
{

class Settings;

}

class QWidget;

class ActionList : public QPx::ActionList
{
    Q_OBJECT

public:
    explicit ActionList(QPx::Settings &settings, QWidget *parent);

    QPx::Action *add(const QString &id, const QString &text, const QKeySequence &shortcut, const QIcon &icon, QPx::ActionList::Enable enable = QPx::ActionList::Enable::On);
    QPx::Action *add(const QString &id, const QString &text, const QKeySequence &shortcut, QPx::ActionList::Enable enable = QPx::ActionList::Enable::On);
    QPx::Action *add(const QString &id, const QString &text, QPx::ActionList::Enable enable = QPx::ActionList::Enable::On);

    QPx::Action *addCheckable(const QString &id, const QString &text, bool state, QPx::ActionList::Enable enable = QPx::ActionList::Enable::On);

public slots:
    void sync();

private:
    QPx::Settings &settings;
};

#endif // ACTIONLIST_H
