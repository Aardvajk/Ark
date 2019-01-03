#ifndef STOREDVARIANT_H
#define STOREDVARIANT_H

#include "properties/custom/Selection.h"

#include <QtCore/QVariant>

class StoredVariant
{
public:
    StoredVariant() : index(-1), subIndex(-1) { }
    StoredVariant(Selection::Type type, const QString &id, int index, int subIndex, const QVariant &old, const QVariant &value) : type(type), id(id), index(index), subIndex(subIndex), old(old), value(value) { }

    Selection::Type type;

    QString id;

    int index;
    int subIndex;

    QVariant old;
    QVariant value;
};

#endif // STOREDVARIANT_H
