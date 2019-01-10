#ifndef LAYOUTACTIONS_H
#define LAYOUTACTIONS_H

#include <QtCore/QObject>

class MainWindow;
class ActionList;

class LayoutActions : public QObject
{
    Q_OBJECT

public:
    LayoutActions(ActionList *actions, MainWindow *parent = nullptr);

private:
    ActionList *actions;
};

#endif // LAYOUTACTIONS_H
