#ifndef PROPERTYMAP_H
#define PROPERTYMAP_H

#include "properties/Property.h"

#include <pcx/ordered_map.h>

#include <QPxCore/QPxStdHash.h>

class PropertyMap : public pcx::ordered_map<QString, Property, QPx::StdHash>
{
public:
    PropertyMap() = default;

    Property &operator[](const QString &name){ return pcx::ordered_map<QString, Property, QPx::StdHash>::operator[](name); }
    Property operator[](const QString &name) const;
};

#endif // PROPERTYMAP_H
