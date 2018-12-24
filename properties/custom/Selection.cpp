#include "Selection.h"

namespace
{

const char *types[] = { "None", "Object", "Face", "Vertex" };

}

bool Selection::operator==(const Selection &s) const
{
    return object == s.object && faces == s.faces && vertices == s.vertices;
}

bool Selection::operator!=(const Selection &s) const
{
    return object != s.object || faces != s.faces || vertices != s.vertices;
}

bool Selection::operator<(const Selection &s) const
{
    return true;
}

Selection Selection::merge(const Selection &s) const
{
    Selection r(object || s.object);

    r.faces = faces;
    foreach(int i, s.faces)
    {
        r.faces.insert(i);
    }

    r.vertices = vertices;
    foreach(int i, s.vertices)
    {
        r.vertices.insert(i);
    }

    return r;
}

Selection Selection::remove(const Selection &s) const
{
    Selection r = *this;

    if(s.object) r.object = false;

    foreach(int i, s.faces)
    {
        r.faces.remove(i);
    }

    foreach(int i, s.vertices)
    {
        r.vertices.remove(i);
    }

    return r;
}

bool Selection::any() const
{
    return object || !faces.empty() || !vertices.empty();
}

const char *Selection::typeToString(Type type)
{
    return types[static_cast<int>(type)];
}

Selection::Type Selection::typeFromString(const std::string &text)
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
