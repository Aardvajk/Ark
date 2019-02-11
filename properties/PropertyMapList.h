#ifndef PROPERTYMAPLIST_H
#define PROPERTYMAPLIST_H

#include "properties/PropertyMap.h"

#include <QtCore/QMap>
#include <QtCore/QDataStream>

#include <pcx/optional.h>

class PropertyMapList
{
public:
    PropertyMapList();

    using PropertyMapDefaultFunc = void(*)(PropertyMap&);
    void setDefaultFunction(PropertyMapDefaultFunc func);

    PropertyMap &operator[](int index);
    PropertyMap operator[](int index) const;

    void saveToStream(QDataStream &ds) const;
    void loadFromStream(QDataStream &ds);

    int count() const { return data.count(); }

private:
    QMap<int, PropertyMap> data;
    PropertyMapDefaultFunc def;

    mutable pcx::optional<PropertyMap> cache;
};

QDataStream &operator<<(QDataStream &ds, const PropertyMapList &map);
QDataStream &operator>>(QDataStream &ds, PropertyMapList &map);

#endif // PROPERTYMAPLIST_H
