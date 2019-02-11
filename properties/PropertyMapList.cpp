#include "PropertyMapList.h"

PropertyMapList::PropertyMapList() : def(nullptr)
{
}

void PropertyMapList::setDefaultFunction(PropertyMapDefaultFunc func)
{
    def = func;
}

PropertyMap &PropertyMapList::operator[](int index)
{
    auto it = data.find(index);
    if(it == data.end())
    {
        it = data.insert(index, PropertyMap());
        if(def)
        {
            def(it.value());
        }

        return it.value();
    }

    return it.value();
}

PropertyMap PropertyMapList::operator[](int index) const
{
    auto it = data.find(index);
    if(it == data.end())
    {
        if(!cache)
        {
            cache = PropertyMap();
            if(def)
            {
                def(*cache);
            }
        }

        return *cache;
    }

    return it.value();
}

void PropertyMapList::saveToStream(QDataStream &ds) const
{
    ds << data.keys().count();
    for(int i: data.keys())
    {
        ds << i << data[i];
    }
}

void PropertyMapList::loadFromStream(QDataStream &ds)
{
    int n;
    ds >> n;

    for(int i = 0; i < n; ++i)
    {
        int index;
        ds >> index;

        ds >> (*this)[index];
    }
}

QDataStream &operator<<(QDataStream &ds, const PropertyMapList &map)
{
    map.saveToStream(ds);
    return ds;
}

QDataStream &operator>>(QDataStream &ds, PropertyMapList &map)
{
    map.loadFromStream(ds);
    return ds;
}
