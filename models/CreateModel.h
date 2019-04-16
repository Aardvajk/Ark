#ifndef CREATEMODEL_H
#define CREATEMODEL_H

#include <QPxCore/QPxTreeModel.h>

class CreateModel : public QPx::TreeModel
{
public:
    explicit CreateModel(QObject *parent = nullptr);

    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
};

#endif // CREATEMODEL_H
