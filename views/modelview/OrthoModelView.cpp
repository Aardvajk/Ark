#include "OrthoModelView.h"

#include "maths/Projection.h"

#include "models/Model.h"

#include "graphics/OrthoGrid.h"

OrthoModelView::OrthoModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent) : ModelView(model, graphics, state, parent)
{
}

Gx::Matrix OrthoModelView::projectionMatrix(const RenderParams &params) const
{
    return Projection::orthoMatrix(params.projection, params.size, params.camera.position());
}

void OrthoModelView::updateCamera(float delta)
{
    if(buttons.contains(Qt::RightButton))
    {
        auto pos = st.camera.position();
        float step = 8.0f * delta;

        Gx::Vec3 up, right, forward;
        Projection::orthoDirections(st.projection, up, right, forward);

        if(keys.contains(Qt::Key_W)) pos += up * step;
        if(keys.contains(Qt::Key_S)) pos -= up * step;

        if(keys.contains(Qt::Key_A)) pos -= right * step;
        if(keys.contains(Qt::Key_D)) pos += right * step;

        if(keys.contains(Qt::Key_R)) pos += forward;
        if(keys.contains(Qt::Key_F)) pos -= forward;

        Projection::clampOrthoZ(st.projection, pos);
        st.camera.setPosition(pos);
    }
}

void OrthoModelView::render()
{
    auto params = beginRender();

    auto grid = model->property("Grid");
    if(grid.value<QVariant>().isValid())
    {
        renderOrthoGrid(graphics, params, grid.value<float>(), { 0.65f, 0.65f, 0.65f });
    }

    renderModel(params);
    endRender(params);
}

Gx::Color OrthoModelView::background() const
{
    return Gx::Color(0.7f, 0.7f, 0.7f);
}

