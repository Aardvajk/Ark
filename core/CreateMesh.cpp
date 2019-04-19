#include "CreateMesh.h"

#include "maths/Grid.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QVariant>

namespace
{

QPair<Gx::Vec3, Gx::Vec3> cuboidCorners(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor)
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

    return qMakePair(a, b);
}

Mesh cuboidMesh(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor)
{
    auto p = cuboidCorners(projection, start, pos, grid, cursor);
    return Mesh::cuboidFromCorners(p.first, p.second);
}

Mesh wedgeMesh(Projection::Type projection, const Gx::Vec3 &start, const Gx::Vec3 &pos, const QVariant &grid, const Gx::Vec3 &cursor)
{
    auto p = cuboidCorners(projection, start, pos, grid, cursor);

    auto min = p.first;
    auto max = p.second;

    float midx = min.x + ((max.x - min.x) / 2);

    QVector<Gx::Vec3> vertices;

    vertices.append(Gx::Vec3(min.x, min.y, min.z));
    vertices.append(Gx::Vec3(min.x, min.y, max.z));
    vertices.append(Gx::Vec3(max.x, min.y, max.z));
    vertices.append(Gx::Vec3(max.x, min.y, min.z));

    vertices.append(Gx::Vec3(midx, max.y, max.z));
    vertices.append(Gx::Vec3(midx, max.y, min.z));

    QVector<Face> faces;

    faces.append({ 0, 3, 2, 1 });
    faces.append({ 0, 1, 4, 5 });
    faces.append({ 2, 3, 5, 4 });
    faces.append({ 0, 5, 3 });
    faces.append({ 1, 2, 4 });

    return Mesh(vertices, faces);
}

}

CreateMesh::Type CreateMesh::fromString(const QString &text)
{
    static const char *s[] = { "Primitives.Cuboid", "Primitives.Wedge", "" };

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
        case Type::Wedge: return wedgeMesh(projection, start, pos, grid, cursor);

        default: break;
    }

    return { };
}
