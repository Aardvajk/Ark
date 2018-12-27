#include "ModelViewRelay.h"

ModelViewRelay::ModelViewRelay(QObject *parent) : QObject(parent)
{
}

void ModelViewRelay::mousePressedSlot(ModelView *view, QMouseEvent *event)
{
    emit mousePressed(view, event);
}

void ModelViewRelay::mouseMovedSlot(ModelView *view, QMouseEvent *event)
{
    emit mouseMoved(view, event);
}

void ModelViewRelay::mouseReleasedSlot(ModelView *view, QMouseEvent *event)
{
    emit mouseReleased(view, event);
}

void ModelViewRelay::renderSlot(ModelView *view, Graphics *graphics, const RenderParams &params)
{
    emit render(view, graphics, params);
}
