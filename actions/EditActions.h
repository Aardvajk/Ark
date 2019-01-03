#ifndef EDITACTIONS_H
#define EDITACTIONS_H

#include <QtCore/QObject>

class Model;
class ActionList;

class EditActions : public QObject
{
    Q_OBJECT

public:
    EditActions(Model *model, ActionList *actions, QObject *parent);

private slots:
    void undoStateChanged();

private:
    Model *model;
    ActionList *actions;
};

#endif // EDITACTIONS_H
