#include "ModelView.h"

#include "models/Model.h"
#include "models/ModelBuffers.h"

#include "graphics/Graphics.h"
#include "graphics/RenderState.h"

#include "graphics/buffers/PreviewBuffer.h"
#include "graphics/buffers/FaceBuffer.h"
#include "graphics/buffers/PointBuffer.h"

#include <QGxMaths/QGxColor.h>

#include <GxMaths/GxRange.h>
#include <GxMaths/GxSize.h>

#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>

ModelView::ModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent) : QGx::GraphicsWidget(graphics->device, parent), model(model), graphics(graphics), st(state)
{
    setAttribute(Qt::WA_MouseTracking);
    setFocusPolicy(Qt::StrongFocus);
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

    p.camera = st.camera;

    auto look = Gx::Vec3(0, 0, 1).transformedNormal(st.camera.rotation().matrix());
    auto up = Gx::Vec3(0, 1, 0).transformedNormal(st.camera.rotation().matrix());

    p.view = Gx::Matrix::lookAt(st.camera.position(), st.camera.position() + look, up);
    p.proj = projectionMatrix(p);

    p.light = st.camera.position();

    return p;
}

void ModelView::setState(const ModelViewState &value)
{
    st = value;
}

void ModelView::paintEvent(QPaintEvent *event)
{
    updateCamera(timer.elapsed(Gx::Timer::Flag::Restart));
    render();
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

    if(prevMousePos)
    {
        updateMousePos(event, mousePos, *prevMousePos);
    }

    prevMousePos = mousePos;
    emit mouseMoved(this, event);
}

void ModelView::mouseReleaseEvent(QMouseEvent *event)
{
    buttons.remove(event->button());
    emit mouseReleased(this, event);
}

void ModelView::updateMousePos(QMouseEvent *event, const Gx::Vec2 &mousePos, const Gx::Vec2 &prevMousePos)
{
}

RenderParams ModelView::beginRender()
{
    graphics->device.begin(this);
    graphics->device.clear(background(), 1.0f);

    return renderParams();
}

void ModelView::renderModel(const RenderParams &params)
{
    if(st.render == Render::Type::Flat || st.render == Render::Type::Textured)
    {
        if(auto r = RenderState(params.projection == Projection::Type::Perspective ? RenderState::Type::Preview : RenderState::Type::Flat, { }, graphics, params))
        {
            model->buffers()->previewBuffer()->renderTriangleList(graphics->device);
        }
    }
    else if(st.render == Render::Type::Wireframe)
    {
        if(auto r = RenderState(RenderState::Type::Color, { }, graphics, params))
        {
            model->buffers()->wireframeBuffer()->renderLineList(graphics->device);
        }
    }

    if(auto r = RenderState(RenderState::Type::Color, RenderState::Flag::NoZ | RenderState::Flag::NoZWrite, graphics, params))
    {
        if(st.render != Render::Type::Wireframe)
        {
            model->buffers()->faceBuffer()->renderLineList(graphics->device);
        }

        model->buffers()->pointBuffer()->renderPointList(graphics->device);
    }
}

void ModelView::endRender(const RenderParams &params)
{
    emit render(this, graphics, params);

    graphics->device.end(this);
}
