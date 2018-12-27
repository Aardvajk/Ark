#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tools/Tool.h"

class Model;
class ActionList;

class MoveTool : public Tool
{
    Q_OBJECT

public:
    MoveTool(Model *model, ActionList *actions, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QPixmap icon() const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params) override;
};

#endif // MOVETOOL_H
