#ifndef SETTINGSCHECKBOX_H
#define SETTINGSCHECKBOX_H

#include <QtWidgets/QCheckBox>

#include <pcx/scoped_lock.h>

namespace QPx
{

class Settings;

}

class SettingsCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    SettingsCheckBox(QPx::Settings &settings, const QString &text, QWidget *parent = 0);

private slots:
    void stateChanged(bool state);
    void settingsChanged(const QVariant &value);

private:
    QPx::Settings &settings;
    pcx::lock lock;
};

#endif // SETTINGSCHECKBOX_H
