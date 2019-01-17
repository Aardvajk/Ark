#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tools/Tool.h"

#include "tools/components/Marquee.h"

class ActionList;
class Model;

class SelectTool : public Tool
{
    Q_OBJECT

public:
    SelectTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QPixmap icon() const override;

    virtual void addOptions(QPx::VBoxLayout *layout) const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params) override;

    virtual void focusLost() override;

private:
    Model *model;
    Marquee mq;
};

#endif // SELECTTOOL_H
