#ifndef CURSORTOOL_H
#define CURSORTOOL_H

#include "tools/Tool.h"

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

class ActionList;
class Model;
class ModelView;

class CursorTool : public Tool
{
    Q_OBJECT

public:
    CursorTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QIcon icon() const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params) override;

    virtual void focusLost() override;

private:
    Model *model;
    ModelView *mv;
    pcx::optional<Gx::Vec3> pos;
};

#endif // CURSORTOOL_H
