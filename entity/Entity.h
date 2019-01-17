#ifndef ENTITY_H
#define ENTITY_H

#include "core/Element.h"

#include "properties/PropertyMap.h"
#include "properties/PropertyMapList.h"

#include <QtCore/QHash>

#include <pcx/shared_data.h>

class Entity
{
public:
    using SubPropertyMap = QMap<Element::Type, PropertyMapList>;

    enum class Type
    {
        Geometry,
        Invalid
    };

    Entity(Type type = Type::Invalid);

    Type type() const { return s.value().type; }

    PropertyMap &properties(){ return s.value().props; }
    const PropertyMap &properties() const { return s.value().props; }

    SubPropertyMap &subProperties(){ return s.value().subProps; }
    const SubPropertyMap &subProperties() const { return s.value().subProps; }

    static const char *typeToString(Type type);
    static Type typeFromString(const std::string &text);

private:
    struct Data
    {
        Type type;
        PropertyMap props;
        SubPropertyMap subProps;
    };

    pcx::shared_data<Data> s;
};

#endif // ENTITY_H
