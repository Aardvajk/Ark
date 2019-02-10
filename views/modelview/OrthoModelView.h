#ifndef ORTHOMODELVIEW_H
#define ORTHOMODELVIEW_H

#include "views/modelview/ModelView.h"

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

class OrthoModelView : public ModelView
{
    Q_OBJECT

public:
    OrthoModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    virtual Gx::Matrix projectionMatrix(const RenderParams &params) const override;

    virtual void render() override;

    virtual Gx::Color background() const override;

private:
    void renderGrid(const RenderParams &params);

    pcx::optional<Gx::Vec3> mv;
};

#endif // ORTHOMODELVIEW_H
