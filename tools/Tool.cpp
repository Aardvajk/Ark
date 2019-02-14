#include "Tool.h"

#include "models/Model.h"

#include "controls/SettingsCheckBox.h"

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxLayouts.h>

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

void Tool::addGridSnapCheckbox(QPx::VBoxLayout *layout) const
{
    layout->addWidget(new SettingsCheckBox(settings["Global"]["Snap.Grid"], "Snap To Grid"));
}

QVariant Tool::gridValue(Model *model) const
{
    return settings["Global"]["Snap.Grid"].value<bool>() ? model->property("Grid").value<QVariant>() : QVariant();
}
