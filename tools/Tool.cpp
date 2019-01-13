#include "Tool.h"

Tool::Tool(QObject *parent) : QObject(parent)
{
}

void Tool::select()
{
    emit selected(this);
}

void Tool::mousePressed(ModelView *view, QMouseEvent *event)
{
}

void Tool::mouseMoved(ModelView *view, QMouseEvent *event)
{
}

void Tool::mouseReleased(ModelView *view, QMouseEvent *event)
{
}

void Tool::render(ModelView *view, Graphics *graphics, const RenderParams &params)
{
}

