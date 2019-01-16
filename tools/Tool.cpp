#include "Tool.h"

Tool::Tool(QPx::Settings &settings, QObject *parent) : QObject(parent), settings(settings)
{
}

void Tool::addOptions(QPx::VBoxLayout *layout) const
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

void Tool::focusLost()
{
}
