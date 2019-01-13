#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tools/Tool.h"

class ActionList;
class Model;

class SelectTool : public Tool
{
    Q_OBJECT

public:
    SelectTool(ActionList *actions, Model *model, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QPixmap icon() const override;

public slots:
    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);
};

#endif // SELECTTOOL_H
