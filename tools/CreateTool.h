#ifndef CREATETOOL_H
#define CREATETOOL_H

#include "tools/Tool.h"

#include <GxMaths/GxVector.h>

class ActionList;
class Model;
class CreateEntityCommand;

class CreateTool : public Tool
{
    Q_OBJECT

public:
    CreateTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QIcon icon() const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void focusLost() override;

private:
    Model *model;
    CreateEntityCommand *command;
    Gx::Vec3 start;
};

#endif // CREATETOOL_H
