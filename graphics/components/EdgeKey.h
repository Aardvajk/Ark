#ifndef EDGEKEY_H
#define EDGEKEY_H

#include <QtCore/QPair>
#include <QtCore/QHash>

class EdgeKey
{
public:
    EdgeKey(int a, int b) : keys(a < b ? qMakePair(a, b) : qMakePair(b, a)) { }

    bool operator==(const EdgeKey &o) const { return keys == o.keys; }

    QPair<int, int> keys;
};

inline uint qHash(const EdgeKey &key){ return qHash(key.keys); }

#endif // EDGEKEY_H
