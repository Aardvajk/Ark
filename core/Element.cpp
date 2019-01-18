#include "Element.h"

const char *Element::toString(Type type)
{
    static const char *s[] = { "Model", "Object", "Face", "Vertex", "None" };

    return s[static_cast<int>(type)];
}
