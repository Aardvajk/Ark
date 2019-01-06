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

    Type type() const { return s.value().type; }

    PropertyMap &properties(){ return s.value().props; }
    const PropertyMap &properties() const { return s.value().props; }

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
