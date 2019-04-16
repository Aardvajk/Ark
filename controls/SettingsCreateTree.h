#ifndef SETTINGSCREATETREE_H
#define SETTINGSCREATETREE_H

#include <QtWidgets/QTreeView>

#include <pcx/scoped_lock.h>

namespace QPx
{

class Settings;

}

class CreateModel;

class SettingsCreateTree : public QTreeView
{
    Q_OBJECT

public:
    SettingsCreateTree(QPx::Settings &settings, QWidget *parent = nullptr);

private slots:
    void stateChanged(const QModelIndex &index,const QModelIndex&);
    void settingsChanged(const QVariant &value);

private:
    QPx::Settings &settings;
    pcx::lock lock;

    CreateModel *model;
};

#endif // SETTINGSCREATETREE_H
