#include "SettingsCreateTree.h"

#include "models/CreateModel.h"

#include <QPxCore/QPxSettings.h>

#include <QtWidgets/QHeaderView>

SettingsCreateTree::SettingsCreateTree(QPx::Settings &settings, QWidget *parent) : QTreeView(parent), settings(settings)
{
    header()->hide();

    model = new CreateModel(this);
    setModel(model);

    connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(stateChanged(QModelIndex,QModelIndex)));
    connect(&settings, SIGNAL(valueChanged(QVariant)), SLOT(settingsChanged(QVariant)));

    settingsChanged(settings.value<QVariant>());
}

void SettingsCreateTree::stateChanged(const QModelIndex &index, const QModelIndex&)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        settings.setValue(QString("%1.%2").arg(index.parent().data(Qt::DisplayRole).toString()).arg(index.data(Qt::DisplayRole).toString()));
    }
}

void SettingsCreateTree::settingsChanged(const QVariant &value)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        for(int i = 0; i < model->rowCount(); ++i)
        {
            QModelIndex parent = model->index(i, 0);
            QString prefix = parent.data(Qt::DisplayRole).toString();

            for(int j = 0; j < model->rowCount(parent); ++j)
            {
                QModelIndex index = model->index(j, 0, parent);
                if(QString("%1.%2").arg(prefix).arg(index.data(Qt::DisplayRole).toString()) == value.toString())
                {
                    selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
                    return;
                }
            }
        }
    }
}
