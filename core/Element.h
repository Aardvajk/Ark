#ifndef ELEMENT_H
#define ELEMENT_H

#include <QPxCore/QPxMetaType.h>

#include <QtCore/QObject>

class Element : public QObject
{
    Q_OBJECT

public:
    enum class Type { Model, Object, Face, Vertex, None };
    Q_ENUM(Type)

    Element() = default;

    static const char *toString(Type type);
};

template<> struct qpx_is_meta_enum<Element::Type> : std::true_type { };

#endif // ELEMENT_H
