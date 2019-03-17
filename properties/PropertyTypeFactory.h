#ifndef PROPERTYTYPEFACTORY_H
#define PROPERTYTYPEFACTORY_H

#include "properties/Property.h"

#include <QtCore/QObject>

#include <pcx/aligned_store.h>

namespace QPx
{

class PropertyBrowserType;

}

class Model;

class PropertyTypeFactory : public QObject
{
    Q_OBJECT

public:
    PropertyTypeFactory(const Model *model, QObject *parent = nullptr);

    QPx::PropertyBrowserType *type(int typeId, Property::SubType subType) const;

private:
    pcx::aligned_store<32> cache;
};

#endif // PROPERTYTYPEFACTORY_H
