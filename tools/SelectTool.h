#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tools/Tool.h"

#include "tools/components/Marquee.h"

class Model;
class ActionList;

class SelectTool : public Tool
{
    Q_OBJECT

public:
    SelectTool(Model *model, ActionList *actions, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QPixmap icon() const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params) override;

    virtual void focusLost() override;

private:
    Marquee mq;
};

#endif // SELECTTOOL_H
