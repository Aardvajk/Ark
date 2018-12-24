#include "PropertyMap.h"

Property PropertyMap::operator[](const QString &name) const
{
    auto i = find(name);
    return i == end() ? Property() : i->second;
}
