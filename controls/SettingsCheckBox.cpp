#include "SettingsCheckBox.h"

#include <QPxCore/QPxSettings.h>

SettingsCheckBox::SettingsCheckBox(QPx::Settings &settings, const QString &text, QWidget *parent) : QCheckBox(text, parent), settings(settings)
{
    settingsChanged(settings.value());
    connect(this, SIGNAL(toggled(bool)), SLOT(stateChanged(bool)));
    connect(&settings, SIGNAL(valueChanged(QVariant)), SLOT(settingsChanged(QVariant)));
}

void SettingsCheckBox::stateChanged(bool state)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        settings.setValue(state);
    }
}

void SettingsCheckBox::settingsChanged(const QVariant &value)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        setChecked(value.toBool());
    }
}
