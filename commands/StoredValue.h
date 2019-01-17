#ifndef STOREDVALUE_H
#define STOREDVALUE_H

#include "core/Element.h"

#include <QtCore/QVariant>

class StoredValue
{
public:
    StoredValue() : index(-1), subIndex(-1) { }
    StoredValue(Element::Type type, const QString &id, int index, int subIndex, const QVariant &old, const QVariant &value) : type(type), id(id), index(index), subIndex(subIndex), old(old), value(value) { }

    Element::Type type;
    QString id;

    int index;
    int subIndex;

    QVariant old;
    QVariant value;
};

#endif // STOREDVALUE_H
