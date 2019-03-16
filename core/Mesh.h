#ifndef MESH_H
#define MESH_H

#include "core/Face.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QVector>
#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

class Mesh
{
public:
    Mesh() = default;
    Mesh(const QVector<Gx::Vec3> &vertices, const QVector<Face> &faces) : vertices(vertices), faces(faces) { }

    Gx::Vec3 vertex(int face, int index) const;
    Gx::Vec3 faceNormal(int face) const;

    void computeTexCoords(int face, const Gx::Vec2 &scale, const Gx::Vec2 &offset);

    Mesh moved(const Gx::Vec3 &distance) const;

    Mesh &set(const Mesh &value);

    static Mesh cuboid(const Gx::Vec3 &dims);
    static Mesh cuboidFromCorners(const Gx::Vec3 &min, const Gx::Vec3 &max);

    QVector<Gx::Vec3> vertices;
    QVector<Face> faces;
};

Q_DECLARE_METATYPE(Mesh)

QDataStream &operator<<(QDataStream &ds, const Mesh &mesh);
QDataStream &operator>>(QDataStream &ds, Mesh &mesh);

#endif // MESH_H
