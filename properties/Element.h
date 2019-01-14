#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtCore/QHash>

namespace Element
{

enum class Type { Object, Face, Vertex, None };

inline uint qHash(Type type, uint seed){ return ::qHash(static_cast<uint>(type), seed); }

const char *toString(Type type);

}

#endif // ELEMENT_H
