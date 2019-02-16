#ifndef EXPORTACTIONS_H
#define EXPORTACTIONS_H

#include <QtCore/QObject>

class Model;
class ActionList;

class ExportActions : public QObject
{
    Q_OBJECT

public:
    ExportActions(Model *model, ActionList *actions, QWidget *parent = nullptr);

private slots:
    void save();
    void saveAs();

private:
    QWidget *widget;
    Model *model;
};

#endif // EXPORTACTIONS_H
