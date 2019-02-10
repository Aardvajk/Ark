#include "OrthoModelView.h"

#include "maths/Projection.h"

#include "models/Model.h"

#include "graphics/OrthoGrid.h"
#include "graphics/RenderPrimitives.h"

#include <GxMaths/GxRay.h>

#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

OrthoModelView::OrthoModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent) : ModelView(model, graphics, state, parent)
{
}

void OrthoModelView::mousePressEvent(QMouseEvent *event)
{
    ModelView::mousePressEvent(event);

    if(event->button() == Qt::RightButton)
    {
        auto p = renderParams();
        mv = Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position;
    }
}

void OrthoModelView::mouseMoveEvent(QMouseEvent *event)
{
    if(mv)
    {
        auto pos = st.camera.position();

        auto p = renderParams();
        pos += (*mv - Gx::Ray::compute(Gx::Vec2(event->pos().x(), event->pos().y()), p.size, p.view, p.proj).position);

        st.camera.setPosition(pos);
    }

    ModelView::mouseMoveEvent(event);
}

void OrthoModelView::mouseReleaseEvent(QMouseEvent *event)
{
    mv = { };

    ModelView::mouseReleaseEvent(event);
}

void OrthoModelView::wheelEvent(QWheelEvent *event)
{
    if(!(event->buttons() & Qt::RightButton))
    {
        auto pos = st.camera.position();
        float step = 4.0f * (static_cast<float>(event->angleDelta().y()) / 120.0f);

        Gx::Vec3 up, right, forward;
        Projection::orthoDirections(st.projection, up, right, forward);

        pos += forward * step;

        Projection::clampOrthoZ(st.projection, pos);
        st.camera.setPosition(pos);
    }

    ModelView::wheelEvent(event);
}

Gx::Matrix OrthoModelView::projectionMatrix(const RenderParams &params) const
{
    return Projection::orthoMatrix(params.projection, params.size, params.camera.position());
}

void OrthoModelView::render()
{
    auto params = beginRender();

    auto grid = model->property("Grid").value<QVariant>();
    if(grid.isValid())
    {
        renderOrthoGrid(graphics, params, grid.value<float>(), { 0.65f, 0.65f, 0.65f });
    }

    RenderPrimitives::cursor(graphics, params, RenderState::Flag::NoZ | RenderState::Flag::NoZWrite, model->property("Cursor").value<Gx::Vec3>(), Gx::Color(0.57f, 0.57f, 0.57f));

    renderModel(params);
    endRender(params);
}

Gx::Color OrthoModelView::background() const
{
    return Gx::Color(0.7f, 0.7f, 0.7f);
}

