#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tools/Tool.h"

#include <GxMaths/GxVector.h>

class ActionList;
class Model;
class MoveSelectionCommand;

class MoveTool : public Tool
{
    Q_OBJECT

public:
    MoveTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QIcon icon() const override;

    virtual void addOptions(QPx::VBoxLayout *layout) const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void focusLost() override;

private slots:
    void rotate();

private:
    Model *model;
    MoveSelectionCommand *command;
    Gx::Vec3 start;
};

#endif // MOVETOOL_H
