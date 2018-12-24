#include "Mesh.h"

bool Mesh::operator==(const Mesh &m) const
{
    return vertices == m.vertices && faces == m.faces;
}

bool Mesh::operator!=(const Mesh &m) const
{
    return vertices != m.vertices || faces != m.faces;
}

bool Mesh::operator<(const Mesh &m) const
{
    return true;
}

Gx::Vec3 Mesh::vertex(int face, int index) const
{
    return vertices[faces[face].elements[index].index];
}

Gx::Vec3 Mesh::faceNormal(int face) const
{
    Gx::Vec3 a = vertex(face, 0);
    Gx::Vec3 b = vertex(face, 1) - a;
    Gx::Vec3 c = vertex(face, 2) - a;

    return b.cross(c).normalized();
}

Mesh Mesh::cuboid(const Gx::Vec3 &dims)
{
    QVector<Gx::Vec3> vertices;

    Gx::Vec3 d = dims / 2;

    vertices.append(Gx::Vec3(-d.x, d.y, -d.z));
    vertices.append(Gx::Vec3(d.x, d.y, -d.z));
    vertices.append(Gx::Vec3(d.x, -d.y, -d.z));
    vertices.append(Gx::Vec3(-d.x, -d.y, -d.z));

    vertices.append(Gx::Vec3(-d.x, d.y, d.z));
    vertices.append(Gx::Vec3(d.x, d.y, d.z));
    vertices.append(Gx::Vec3(d.x, -d.y, d.z));
    vertices.append(Gx::Vec3(-d.x, -d.y, d.z));

    QVector<Face> faces;

    faces.append({ 0, 1, 2, 3 });
    faces.append({ 1, 5, 6, 2 });
    faces.append({ 4, 0, 3, 7 });
    faces.append({ 5, 4, 7, 6 });
    faces.append({ 4, 5, 1, 0 });
    faces.append({ 3, 2, 6, 7 });

    return Mesh(vertices, faces);
}

QDataStream &operator<<(QDataStream &ds, const Mesh &mesh)
{
    ds << mesh.vertices.count();
    for(auto &v: mesh.vertices)
    {
        ds << v.x << v.y << v.z;
    }

    ds << mesh.faces.count();
    for(auto &f: mesh.faces)
    {
        ds << f.elements.count();
        for(auto &e: f.elements)
        {
            ds << e.index;
        }
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, Mesh &mesh)
{
    mesh = Mesh();

    int n, m;

    ds >> n;
    for(int i = 0; i < n; ++i)
    {
        Gx::Vec3 v;
        ds >> v.x >> v.y >> v.z;

        mesh.vertices.append(v);
    }

    ds >> n;
    for(int i = 0; i < n; ++i)
    {
        Face f;

        ds >> m;
        for(int j = 0; j < m; ++j)
        {
            Face::Element e;
            ds >> e.index;

            f.elements.append(e);
        }

        mesh.faces.append(f);
    }

    return ds;
}
