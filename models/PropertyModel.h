#ifndef PROPERTYMODEL_H
#define PROPERTYMODEL_H

#include "core/Element.h"

#include <QPxPropertyBrowser/QPxPropertyBrowserModel.h>

class Model;
class PropertyTypeFactory;

class PropertyModel : public QPx::PropertyBrowserModel
{
    Q_OBJECT

public:
    PropertyModel(Element::Type type, Model *model, PropertyTypeFactory *factory, QObject *parent = nullptr);

private slots:
    void selectionChanged();
    void valueChanged(const QVariant &value);

private:
    Element::Type type;
    Model *model;
    PropertyTypeFactory *factory;
};

#endif // PROPERTYMODEL_H
