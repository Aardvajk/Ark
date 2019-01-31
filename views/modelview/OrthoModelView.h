#ifndef ORTHOMODELVIEW_H
#define ORTHOMODELVIEW_H

#include "views/modelview/ModelView.h"

class OrthoModelView : public ModelView
{
    Q_OBJECT

public:
    OrthoModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent = nullptr);

protected:
    virtual Gx::Matrix projectionMatrix(const RenderParams &params) const override;

    virtual void updateCamera(float delta);

    virtual void render() override;

    virtual Gx::Color background() const override;

private:
    void renderGrid(const RenderParams &params);
};

#endif // ORTHOMODELVIEW_H
