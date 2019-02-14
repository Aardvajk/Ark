#ifndef SELECTACTIONS_H
#define SELECTACTIONS_H

#include <QtCore/QObject>

namespace QPx
{

class Settings;

}

class Model;
class ActionList;

class SelectActions : public QObject
{
    Q_OBJECT

public:
    SelectActions(Model *model, ActionList *actions, QPx::Settings &settings, QObject *parent = nullptr);

private slots:
    void modelChanged();

    void all();
    void none();

    void prevFace();
    void nextFace();

    void wholeObject();

private:
    Model *model;
    ActionList *actions;
    QPx::Settings &settings;
};

#endif // SELECTACTIONS_H
