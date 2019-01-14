#ifndef SELECTION_H
#define SELECTION_H

#include "properties/Element.h"

#include <QtCore/QMetaType>
#include <QtCore/QHash>
#include <QtCore/QSet>

class Selection
{
public:
    explicit Selection(bool object = false);
    Selection(const QSet<int> &faces, const QSet<int> &vertices);

    bool operator==(const Selection &s) const;
    bool operator!=(const Selection &s) const;
    bool operator<(const Selection &s) const;

    bool object;
    QHash<Element::Type, QSet<int> > elements;
};

Q_DECLARE_METATYPE(Selection)

#endif // SELECTION_H
