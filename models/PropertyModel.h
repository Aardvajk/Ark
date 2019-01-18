#ifndef PROPERTYMODEL_H
#define PROPERTYMODEL_H

#include <QPxPropertyBrowser/QPxPropertyBrowserModel.h>

class Model;

class PropertyModel : public QPx::PropertyBrowserModel
{
    Q_OBJECT

public:
    PropertyModel(Model *model, QObject *parent = nullptr);

private slots:
    void selectionChanged();

private:
    Model *model;
};

#endif // PROPERTYMODEL_H
