#ifndef SELECTACTIONS_H
#define SELECTACTIONS_H

#include <QtCore/QObject>

class Model;
class ActionList;

class SelectActions : public QObject
{
    Q_OBJECT

public:
    SelectActions(Model *model, ActionList *actions, QObject *parent = nullptr);

private slots:
    void modelChanged();

    void prevFace();
    void nextFace();

    void wholeObject();

private:
    Model *model;
    ActionList *actions;
};

#endif // SELECTACTIONS_H
