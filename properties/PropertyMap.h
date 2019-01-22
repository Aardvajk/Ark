#ifndef PROPERTYMAP_H
#define PROPERTYMAP_H

#include "properties/Property.h"

#include <pcx/ordered_map.h>

#include <QPxCore/QPxStdHash.h>

#include <QtCore/QStringList>

#include <pcx/optional.h>

class PropertyMap : public pcx::ordered_map<QString, Property, QPx::StdHash>
{
public:
    PropertyMap() = default;

    QStringList keys() const;

    Property &operator[](const QString &name){ return pcx::ordered_map<QString, Property, QPx::StdHash>::operator[](name); }
    Property operator[](const QString &name) const;

    void invalidate();

private:
    mutable pcx::optional<QStringList> cache;
};

#endif // PROPERTYMAP_H
