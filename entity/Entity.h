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

    QStringList properties() const;
    QStringList subProperties(Element::Type type, int index) const;

    Property property(const QString &name) const;
    Property subProperty(Element::Type type, int index, const QString &name) const;

    void addProperty(const QString &name, const Property &property);
    void addSubProperty(Element::Type type, int index, const QString &name, const Property &property);

    template<typename T> void setProperty(const QString &name, const T &value){ setPropertyVariant(name, QVariant::fromValue(value)); }
    template<typename T> void setSubProperty(Element::Type type, int index, const QString &name, const T &value){ setSubPropertyVariant(type, index, name, QVariant::fromValue(value)); }

    static const char *typeToString(Type type);
    static Type typeFromString(const std::string &text);

private:
    void setPropertyVariant(const QString &name, const QVariant &value);
    void setSubPropertyVariant(Element::Type type, int index, const QString &name, const QVariant &value);

    struct Data
    {
        Type type;
        PropertyMap props;
        SubPropertyMap subProps;
    };

    pcx::shared_data<Data> s;
};

template<> void Entity::setProperty<QVariant>(const QString &name, const QVariant &value){ setPropertyVariant(name, value); }
template<> void Entity::setSubProperty<QVariant>(Element::Type type, int index, const QString &name, const QVariant &value){ setSubPropertyVariant(type, index, name, value); }

#endif // ENTITY_H
