#include "ModelView.h"

#include "graphics/Graphics.h"

#include <GxMaths/GxColor.h>

ModelView::ModelView(Model *model, Graphics *graphics, QWidget *parent) : QGx::GraphicsWidget(graphics->device, parent), graphics(graphics)
{
}

void ModelView::paintEvent(QPaintEvent *event)
{
    graphics->device.begin(this);
    graphics->device.clear({ 0.7f, 0.75f, 0.8f }, 1.0f);
    graphics->device.end(this);
}
