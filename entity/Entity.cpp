#include "Entity.h"

namespace
{

const char *types[] = { "Geometry" };

}

Entity::Entity(Type type) : s(type, PropertyMap(), SubPropertyMap())
{
}

const char *Entity::typeToString(Type type)
{
    return types[static_cast<int>(type)];
}

Entity::Type Entity::typeFromString(const std::string &text)
{
    int i = 0;
    while(types[i][0])
    {
        if(types[i] == text)
        {
            return static_cast<Type>(i);
        }

        ++i;
    }

    return Type::Invalid;
}
