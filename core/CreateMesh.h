#ifndef CREATEMESH_H
#define CREATEMESH_H

#include "core/Mesh.h"

#include "maths/Projection.h"

namespace Gx
{

class Vec3;

}

class QString;
class QVariant;

namespace CreateMesh
{

enum class Type
{
    Cuboid,
    Wedge,
    Invalid
};

Type fromString(const QString &text);
Mesh create(Type type, Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor);

}

#endif // CREATEMESH_H
