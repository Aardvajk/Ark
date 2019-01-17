#include "SettingsElementBox.h"

#include "gui/GuiTextButton.h"
#include "gui/GuiButtonGroup.h"

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxLayouts.h>

#include <pcx/enum_range.h>

SettingsElementBox::SettingsElementBox(QPx::Settings &settings, QWidget *parent) : QWidget(parent), settings(settings)
{
    auto layout = new QPx::HBoxLayout(0, 2, this);
    auto group = new GuiButtonGroup(this);

    for(auto e: pcx::enum_range(Element::Type::Object, Element::Type::None))
    {
        auto button = layout->addTypedWidget(group->addButton(new GuiTextButton(Element::toString(e))));
        button->setProperty("ark-element-type", QVariant::fromValue(e));

        if(e == settings.value<Element::Type>())
        {
            button->setChecked(true);
        }

        map[e] = button;
        connect(button, SIGNAL(toggled(bool)), SLOT(stateChanged(bool)));
    }

    connect(&settings, SIGNAL(valueChanged(QVariant)), SLOT(settingsChanged(QVariant)));
}

void SettingsElementBox::stateChanged(bool state)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        settings.setValue(sender()->property("ark-element-type"));
    }
}

void SettingsElementBox::settingsChanged(const QVariant &value)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        map[value.value<Element::Type>()]->setChecked(true);
    }
}
