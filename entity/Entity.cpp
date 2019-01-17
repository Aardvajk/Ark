#include "Entity.h"

#include "entity/EntityFactory.h"

namespace
{

const char *types[] = { "Geometry" };

}

Entity::Entity(Type type) : s(type, PropertyMap(), SubPropertyMap())
{
    s.value().subProps[Element::Type::Face].setDefaultFunction(EntityFactory::defaultFaceProperties);
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
