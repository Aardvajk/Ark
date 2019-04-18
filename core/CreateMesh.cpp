#include "CreateMesh.h"

#include "maths/Grid.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QVariant>

namespace
{

Mesh cuboidMesh(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor)
{
    auto a = start;
    auto b = pos;

    if(a.x > b.x) qSwap(a.x, b.x);
    if(a.y > b.y) qSwap(a.y, b.y);
    if(a.z > b.z) qSwap(a.z, b.z);

    int x = 0, y = 1, z = 2;

    switch(projection)
    {
        case Projection::Type::Top:
        case Projection::Type::Bottom: x = 2; y = 0; z = 1; break;

        case Projection::Type::Left:
        case Projection::Type::Right: x = 2; z = 0; break;

        default: break;
    }

    if(grid.isValid())
    {
        auto g = grid.value<float>();

        auto ag = Grid::snapCorner(a, g);
        auto bg = Grid::snapCorner(b, g);

        if(a[x] < 0) ag[x] -= g;
        if(b[x] > 0) bg[x] += g;

        if(a[y] < 0) ag[y] -= g;
        if(b[y] < 0) bg[y] -= g;

        bg[y] += g;

        a = ag;
        b = bg;
    }

    b[z] = cursor[z];
    a[z] = b[z] - (grid.isValid() ? grid.value<float>() : 1.0f);

    return Mesh::cuboidFromCorners(a, b);
}

}

CreateMesh::Type CreateMesh::fromString(const QString &text)
{
    static const char *s[] = { "Primitives.Cuboid", "" };

    int i = 0;
    while(s[i][0])
    {
        if(text == s[i])
        {
            return static_cast<Type>(i);
        }

        ++i;
    }

    return Type::Invalid;
}

Mesh CreateMesh::create(Type type, Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor)
{
    switch(type)
    {
        case Type::Cuboid: return cuboidMesh(projection, start, pos, grid, cursor);

        default: break;
    }

    return { };
}
