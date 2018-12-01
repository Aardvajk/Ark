#ifndef APPLICATIONACTIONS_H
#define APPLICATIONACTIONS_H

#include <QtCore/QObject>

class ActionList;
class MainWindow;

class ApplicationActions : public QObject
{
    Q_OBJECT

public:
    ApplicationActions(ActionList *actions, MainWindow *parent);

private slots:
    void showOptions();

private:
    ActionList *actions;
    MainWindow *parent;
};

#endif // APPLICATIONACTIONS_H
