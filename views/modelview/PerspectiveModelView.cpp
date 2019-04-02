#include "PerspectiveModelView.h"

#include "models/Model.h"

#include <GxMaths/GxMatrix.h>
#include <GxMaths/GxRange.h>

#include <QGxMaths/QGxColor.h>

#include <QtGui/QMouseEvent>

PerspectiveModelView::PerspectiveModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent) : ModelView(model, graphics, state, parent)
{
}

Gx::Matrix PerspectiveModelView::projectionMatrix(const RenderParams &params) const
{
    return Gx::Matrix::perspective(params.fov, params.size.width / params.size.height, { 0.1f, 100.0f });
}

void PerspectiveModelView::updateMousePos(QMouseEvent *event, const Gx::Vec2 &mousePos, const Gx::Vec2 &prevMousePos)
{
    if(event->buttons() & Qt::RightButton)
    {
        if(prevMousePos != mousePos)
        {
            float turn = 0.4f;

            Gx::Vec2 dims = Gx::Vec2(sizeF().width, sizeF().height) * 0.5f;
            Gx::Vec2 diff = mousePos - prevMousePos;

            Gx::Vec2 ang = st.camera.angle();

            ang += Gx::Vec2((diff.x / dims.x) * turn, (diff.y / dims.y) * turn);

            st.camera.setAngle(ang);
        }
    }
}

void PerspectiveModelView::updateCamera(float delta)
{
    if(buttons.contains(Qt::RightButton))
    {
        auto pos = st.camera.position();
        float step = 8.0f * delta;

        auto m = Gx::Matrix::rotationY(st.camera.angle().x);

        auto look = Gx::Vec3(0, 0, 1).transformedNormal(m).normalized();
        auto right = Gx::Vec3(1, 0, 0).transformedNormal(m).normalized();

        if(keys.contains(Qt::Key_W)) pos += look * step;
        if(keys.contains(Qt::Key_S)) pos -= look * step;

        if(keys.contains(Qt::Key_A)) pos -= right * step;
        if(keys.contains(Qt::Key_D)) pos += right * step;

        if(keys.contains(Qt::Key_R)) pos.y += step;
        if(keys.contains(Qt::Key_F)) pos.y -= step;

        st.camera.setPosition(pos);
    }
}

void PerspectiveModelView::render()
{
    auto p = beginRender();

    renderModel(p);
    endRender(p);
}

Gx::Color PerspectiveModelView::background() const
{
    return QGx::Color(model->property("Background").value<QColor>());
}
