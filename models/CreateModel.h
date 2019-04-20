#ifndef CREATEMODEL_H
#define CREATEMODEL_H

#include <QPxCore/QPxTreeModel.h>

class Model;

class CreateModel : public QPx::TreeModel
{
    Q_OBJECT

public:
    CreateModel(Model *model, QObject *parent = nullptr);

    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private slots:
    void modelChanged();

private:
    Model *model;
};

#endif // CREATEMODEL_H
