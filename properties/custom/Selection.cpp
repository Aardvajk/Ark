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
