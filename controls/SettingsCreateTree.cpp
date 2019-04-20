#include "SettingsCreateTree.h"

#include "models/CreateModel.h"

#include <QPxCore/QPxSettings.h>

#include <QtWidgets/QHeaderView>

SettingsCreateTree::SettingsCreateTree(Model *model, QPx::Settings &settings, QWidget *parent) : QTreeView(parent), settings(settings)
{
    header()->hide();

    treeModel = new CreateModel(model, this);
    setModel(treeModel);

    connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(stateChanged(QModelIndex,QModelIndex)));
    connect(&settings, SIGNAL(valueChanged(QVariant)), SLOT(settingsChanged(QVariant)));

    settingsChanged(settings.value<QVariant>());

    expandAll();
}

void SettingsCreateTree::stateChanged(const QModelIndex &index, const QModelIndex&)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);

        QString id;
        if(!index.parent().isValid())
        {
            id = index.data(Qt::DisplayRole).toString();
        }
        else
        {
            id = QString("%1.%2").arg(index.parent().data(Qt::DisplayRole).toString()).arg(index.data(Qt::DisplayRole).toString());
        }

        settings.setValue(id);
    }
}

void SettingsCreateTree::settingsChanged(const QVariant &value)
{
    if(!lock)
    {
        auto s = pcx::scoped_lock(lock);
        for(int i = 0; i < treeModel->rowCount(); ++i)
        {
            QModelIndex parent = treeModel->index(i, 0);
            QString prefix = parent.data(Qt::DisplayRole).toString();

            if(prefix == value.toString())
            {
                selectionModel()->setCurrentIndex(parent, QItemSelectionModel::ClearAndSelect);
                return;
            }

            for(int j = 0; j < treeModel->rowCount(parent); ++j)
            {
                QModelIndex index = treeModel->index(j, 0, parent);
                if(QString("%1.%2").arg(prefix).arg(index.data(Qt::DisplayRole).toString()) == value.toString())
                {
                    selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
                    return;
                }
            }
        }
    }
}
