#ifndef CLIPBOARDACTIONS_H
#define CLIPBOARDACTIONS_H

#include <QtCore/QObject>

class Model;
class ActionList;

class ClipboardActions : public QObject
{
    Q_OBJECT

public:
    ClipboardActions(Model *model, ActionList *actions, QObject *parent = nullptr);

private slots:
    void modelChanged();
    void clipboardChanged();

    void cut();
    void copy();
    void paste();

private:
    Model *model;
    ActionList *actions;
};

#endif // CLIPBOARDACTIONS_H
