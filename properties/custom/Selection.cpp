#include "Selection.h"

#include "physics/Mesh.h"

#include <pcx/enum_range.h>

Selection::Selection(const QSet<int> &faces, const QSet<int> &vertices)
{
    elements[Element::Type::Face] = faces;
    elements[Element::Type::Vertex] = vertices;
}

bool Selection::operator==(const Selection &s) const
{
    return elements == s.elements;
}

bool Selection::operator!=(const Selection &s) const
{
    return elements != s.elements;
}

bool Selection::operator<(const Selection &s) const
{
    return true;
}

bool Selection::any() const
{
    for(auto &e: elements)
    {
        if(!e.isEmpty()) return true;
    }

    return false;
}

Selection Selection::merge(const Selection &s) const
{
    Selection r;

    for(auto t: pcx::enum_range(Element::Type::Object, Element::Type::None))
    {
        r.elements[t] = elements[t];
        for(auto i: s.elements[t])
        {
            r.elements[t].insert(i);
        }
    }

    return r;
}

Selection Selection::remove(const Selection &s) const
{
    Selection r = *this;

    for(auto t: s.elements.keys())
    {
        for(auto i: s.elements[t])
        {
            r.elements[t].remove(i);
        }
    }

    return r;
}

QSet<int> Selection::selectedVertices(const Mesh &mesh) const
{
    auto r = elements[Element::Type::Vertex];

    for(auto v: elements[Element::Type::Face])
    {
        for(auto i: mesh.faces[v].elements)
        {
            r.insert(i.index);
        }
    }

    return r;
}

Selection Selection::fromElements(Element::Type type, int count)
{
    Selection s;
    for(int i = 0; i < count; ++i)
    {
        s.elements[type].insert(i);
    }

    return s;
}
