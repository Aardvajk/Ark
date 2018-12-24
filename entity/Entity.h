#ifndef ENTITY_H
#define ENTITY_H

#include "properties/PropertyMap.h"

#include <pcx/shared_data.h>

class Entity
{
public:
    enum class Type
    {
        Geometry,
        Invalid
    };

    Entity(Type type = Type::Invalid);

    static const char *typeToString(Type type);
    static Type typeFromString(const std::string &text);

private:
    struct Data
    {
        Type type;
        PropertyMap props;
    };

    pcx::shared_data<Data> s;
};

#endif // ENTITY_H
