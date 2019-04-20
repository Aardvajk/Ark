#ifndef ENTITY_H
#define ENTITY_H

#include "core/Element.h"
#include "core/Selection.h"

#include "properties/PropertyMap.h"
#include "properties/PropertyMapList.h"

#include "core/Mesh.h"

#include <QPxCore/QPxMetaType.h>

#include <QtCore/QHash>
#include <QtCore/QDataStream>

#include <pcx/shared_data.h>

class Entity
{
public:
    using SubPropertyMap = QMap<Element::Type, PropertyMapList>;

    enum class Type
    {
        Geometry,
        DiffuseMap,
        NormalMap,
        Model,
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

    const Selection &selection() const;
    void setSelection(const Selection &value);

    Mesh &mesh();
    const Mesh &mesh() const;
    void setMesh(const Mesh &value);

    void computeTexCoords();

    void saveToStream(QDataStream &ds) const;
    void loadFromStream(QDataStream &ds);

    static const char *typeToString(Type type);
    static Type typeFromString(const std::string &text);
    static bool isResourceType(Type type);
    static bool isThumbnailType(Type type);

private:
    void setPropertyVariant(const QString &name, const QVariant &value);
    void setSubPropertyVariant(Element::Type type, int index, const QString &name, const QVariant &value);

    struct Data
    {
        Type type;
        PropertyMap props;
        SubPropertyMap subProps;
        Selection selection;
        Mesh mesh;
    };

    pcx::shared_data<Data> s;
};

template<> void Entity::setProperty<QVariant>(const QString &name, const QVariant &value){ setPropertyVariant(name, value); }
template<> void Entity::setSubProperty<QVariant>(Element::Type type, int index, const QString &name, const QVariant &value){ setSubPropertyVariant(type, index, name, value); }

template<> struct qpx_is_meta_enum<Entity::Type> : std::true_type { };

QDataStream &operator<<(QDataStream &ds, const Entity &entity);
QDataStream &operator>>(QDataStream &ds, Entity &entity);

#endif // ENTITY_H
