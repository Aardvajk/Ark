#ifndef PROPERTYMAPLIST_H
#define PROPERTYMAPLIST_H

#include "properties/PropertyMap.h"

#include <QtCore/QMap>

#include <pcx/optional.h>

class PropertyMapList
{
public:
    PropertyMapList();

    using PropertyMapDefaultFunc = void(*)(PropertyMap&);
    void setDefaultFunction(PropertyMapDefaultFunc func);

    PropertyMap &operator[](int index);
    PropertyMap operator[](int index) const;

private:
    QMap<int, PropertyMap> data;
    PropertyMapDefaultFunc def;

    mutable pcx::optional<PropertyMap> cache;
};

#endif // PROPERTYMAPLIST_H
