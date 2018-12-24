#ifndef MESH_H
#define MESH_H

#include "properties/custom/Face.h"

#include <GxMaths/GxVector.h>

#include <QtCore/QMetaType>
#include <QtCore/QVector>
#include <QtCore/QDataStream>

class Mesh
{
public:
    Mesh() = default;
    Mesh(const QVector<Gx::Vec3> &vertices, const QVector<Face> &faces) : vertices(vertices), faces(faces) { }

    bool operator==(const Mesh &m) const;
    bool operator!=(const Mesh &m) const;
    bool operator<(const Mesh &m) const;

    static Mesh cuboid(const Gx::Vec3 &dims);

    Gx::Vec3 vertex(int face, int index) const;
    Gx::Vec3 faceNormal(int face) const;

    QVector<Gx::Vec3> vertices;
    QVector<Face> faces;
};

Q_DECLARE_METATYPE(Mesh)

QDataStream &operator<<(QDataStream &ds, const Mesh &mesh);
QDataStream &operator>>(QDataStream &ds, Mesh &mesh);

#endif // MESH_H
