#include "ModelView.h"

#include "models/Model.h"
#include "models/ModelBuffers.h"

#include "properties/Property.h"
#include "properties/PropertyMap.h"

#include "graphics/Graphics.h"
#include "graphics/RenderParams.h"
#include "graphics/RenderState.h"

#include "graphics/buffers/PreviewBuffer.h"
#include "graphics/buffers/FaceBuffer.h"
#include "graphics/buffers/PointBuffer.h"

#include <GxMaths/GxColor.h>
#include <GxMaths/GxRange.h>

#include <QGxMaths/QGxColor.h>

#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>

ModelView::ModelView(Model *model, Graphics *graphics, QWidget *parent) : QGx::GraphicsWidget(graphics->device, parent), model(model), graphics(graphics)
{
    setAttribute(Qt::WA_MouseTracking);
    setFocusPolicy(Qt::StrongFocus);

    st.camera = Gx::Transform({ 0, 0, -6}, { 0, 0 });
}

ModelViewState ModelView::state() const
{
    return st;
}

RenderParams ModelView::renderParams() const
{
    RenderParams p;

    p.size = sizeF();
    p.fov = M_PI * 0.25f;
    p.projection = st.projection;

    p.position = st.camera.position();

    auto look = Gx::Vec3(0, 0, 1).transformedNormal(st.camera.rotation().matrix());
    auto up = Gx::Vec3(0, 1, 0).transformedNormal(st.camera.rotation().matrix());

    p.view = Gx::Matrix::lookAt(st.camera.position(), st.camera.position() + look, up);
    p.proj = Projection::matrix(p);

    p.light = st.camera.position();

    return p;
}

void ModelView::setState(const ModelViewState &state)
{
    st = state;
}

void ModelView::paintEvent(QPaintEvent *event)
{
    updateCamera(timer.elapsed(Gx::Timer::Flag::Restart));
    renderModel();
}

void ModelView::keyPressEvent(QKeyEvent *event)
{
    keys.insert(event->key());
}

void ModelView::keyReleaseEvent(QKeyEvent *event)
{
    keys.remove(event->key());
}

void ModelView::mousePressEvent(QMouseEvent *event)
{
    prevMousePos = Gx::Vec2(event->pos().x(), event->pos().y());

    buttons.insert(event->button());
    emit mousePressed(this, event);
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
    Gx::Vec2 mousePos(event->pos().x(), event->pos().y());

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

    prevMousePos = mousePos;
    emit mouseMoved(this, event);
}

void ModelView::mouseReleaseEvent(QMouseEvent *event)
{
    buttons.remove(event->button());
    emit mouseReleased(this, event);
}

void ModelView::updateCamera(float delta)
{
    if(buttons.contains(Qt::RightButton))
    {
        auto pos = st.camera.position();
        float step = 8.0f * delta;

        Gx::Vec3 look, right;
        st.camera.flatVectors(look, right);

        if(keys.contains(Qt::Key_W)) pos += look * step;
        if(keys.contains(Qt::Key_S)) pos -= look * step;

        if(keys.contains(Qt::Key_A)) pos -= right * step;
        if(keys.contains(Qt::Key_D)) pos += right * step;

        if(keys.contains(Qt::Key_R)) pos.y += step;
        if(keys.contains(Qt::Key_F)) pos.y -= step;

        st.camera.setPosition(pos);
    }
}

void ModelView::renderModel()
{
    graphics->device.begin(this);
    graphics->device.clear(QGx::Color(model->property("Background").value<QColor>()), 1.0f);

    auto params = renderParams();

    if(auto r = RenderState(RenderState::Type::Preview, { }, graphics, params))
    {
        model->buffers()->previewBuffer()->renderTriangleList(graphics->device);
    }

    if(auto r = RenderState(RenderState::Type::Color, { }, graphics, params))
    {
        model->buffers()->faceBuffer()->renderLineList(graphics->device);
        model->buffers()->pointBuffer()->renderPointList(graphics->device);
    }

    emit render(this, graphics, params);

    graphics->device.end(this);
}
