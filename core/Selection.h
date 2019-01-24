#ifndef SELECTION_H
#define SELECTION_H

#include "core/Element.h"

#include <QtCore/QMap>
#include <QtCore/QSet>

class Mesh;

class Selection
{
public:
    Selection() = default;
    Selection(const QSet<int> &faces, const QSet<int> &vertices);

    bool operator==(const Selection &s) const;
    bool operator!=(const Selection &s) const;

    bool any() const;

    Selection merge(const Selection &s) const;
    Selection remove(const Selection &s) const;

    QSet<int> selectedVertices(const Mesh &mesh) const;

    static Selection fromElements(Element::Type type, int count);

    QMap<Element::Type, QSet<int> > elements;
};

#endif // SELECTION_H
