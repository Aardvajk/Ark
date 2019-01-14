#include "Selection.h"

Selection::Selection(bool object) : object(object)
{
}

Selection::Selection(const QSet<int> &faces, const QSet<int> &vertices) : object(false)
{
    elements[Element::Type::Face] = faces;
    elements[Element::Type::Vertex] = vertices;
}

bool Selection::operator==(const Selection &s) const
{
    return object == s.object && elements == s.elements;
}

bool Selection::operator!=(const Selection &s) const
{
    return object != s.object || elements != s.elements;
}

bool Selection::operator<(const Selection &s) const
{
    return true;
}

Selection Selection::merge(const Selection &s) const
{
    Selection r(object || s.object);

    for(auto t: s.elements.keys())
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

    if(s.object) r.object = false;

    for(auto t: s.elements.keys())
    {
        for(auto i: s.elements[t])
        {
            r.elements[t].remove(i);
        }
    }

    return r;
}

