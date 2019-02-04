#ifndef MESH_H
#define MESH_H

#include "core/Face.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QVector>

class Mesh
{
public:
    Mesh() = default;
    Mesh(const QVector<Gx::Vec3> &vertices, const QVector<Face> &faces) : vertices(vertices), faces(faces) { }

    Gx::Vec3 vertex(int face, int index) const;
    Gx::Vec3 faceNormal(int face) const;

    Mesh moved(const Gx::Vec3 &distance) const;

    Mesh &set(const Mesh &value);

    static Mesh cuboid(const Gx::Vec3 &dims);
    static Mesh cuboidFromCorners(const Gx::Vec3 &min, const Gx::Vec3 &max);

    QVector<Gx::Vec3> vertices;
    QVector<Face> faces;
};

#endif // MESH_H
