#include "PropertyModel.h"

#include "models/Model.h"

PropertyModel::PropertyModel(Model *model, QObject *parent) : QPx::PropertyBrowserModel(parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(selectionChanged()));
    selectionChanged();
}

void PropertyModel::selectionChanged()
{
}
