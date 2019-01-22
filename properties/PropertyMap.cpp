#include "PropertyMap.h"

QStringList PropertyMap::keys() const
{
    if(!cache)
    {
        cache = QStringList();
        for(auto i: *this)
        {
            cache->append(i.first);
        }
    }

    return *cache;
}

Property PropertyMap::operator[](const QString &name) const
{
    auto i = find(name);
    return i == end() ? Property() : i->second;
}

void PropertyMap::invalidate()
{
    cache = pcx::nullopt;
}
