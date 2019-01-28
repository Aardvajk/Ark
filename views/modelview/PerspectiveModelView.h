#ifndef PERSPECTIVEMODELVIEW_H
#define PERSPECTIVEMODELVIEW_H

#include "views/modelview/ModelView.h"

class PerspectiveModelView : public ModelView
{
    Q_OBJECT

public:
    PerspectiveModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent = nullptr);

protected:
    virtual Gx::Matrix projectionMatrix(const RenderParams &params) const override;

    virtual void updateMousePos(QMouseEvent *event, const Gx::Vec2 &mousePos, const Gx::Vec2 &prevMousePos) override;
    virtual void updateCamera(float delta) override;

    virtual void render() override;
};

#endif // PERSPECTIVEMODELVIEW_H
