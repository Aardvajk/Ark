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

QDataStream &operator<<(QDataStream &ds, const PropertyMap &pm)
{
    ds << pm.keys().count();
    for(auto key: pm.keys())
    {
        ds << key << pm[key].value<QVariant>();
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, PropertyMap &pm)
{
    int n;
    ds >> n;

    for(int i = 0; i < n; ++i)
    {
        QString key;
        QVariant value;

        ds >> key >> value;

        if(pm.keys().contains(key))
        {
            pm[key].setValue(value);
        }
    }

    return ds;
}
