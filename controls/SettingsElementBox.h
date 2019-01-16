#ifndef SETTINGSELEMENTBOX_H
#define SETTINGSELEMENTBOX_H

#include "core/Element.h"

#include <QtCore/QHash>

#include <QtWidgets/QWidget>

#include <pcx/scoped_lock.h>

namespace QPx
{

class Settings;

}

class GuiButton;

class SettingsElementBox : public QWidget
{
    Q_OBJECT

public:
    SettingsElementBox(QPx::Settings &settings, QWidget *parent = nullptr);

private slots:
    void stateChanged(bool state);
    void settingsChanged(const QVariant &value);

private:
    QPx::Settings &settings;
    QHash<Element::Type, GuiButton*> map;
    pcx::lock lock;
};

#endif // SETTINGSELEMENTBOX_H
