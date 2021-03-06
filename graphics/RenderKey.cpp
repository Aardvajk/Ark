#include "RenderKey.h"

bool RenderKey::operator==(const RenderKey &o) const
{
    return group == o.group && diffuse == o.diffuse && normal == o.normal;
}

uint qHash(const RenderKey &v)
{
    return qHash(v.group) ^ qHash(v.diffuse) ^ qHash(v.normal);
}
