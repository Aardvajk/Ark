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
