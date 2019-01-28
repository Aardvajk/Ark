#ifndef PROJECTION_H
#define PROJECTION_H

#include <QPxCore/QPxMetaType.h>

#include <GxMaths/GxTransform.h>
#include <GxMaths/GxMatrix.h>

#include <QtCore/QObject>

class RenderParams;

class Projection : public QObject
{
    Q_OBJECT

public:
    enum class Type { Perspective, Top, Bottom, Left, Right, Front, Back, None };
    Q_ENUM(Type)

    enum class Direction { Up, Down, Left, Right, Forward, Backward, None };
    Q_ENUM(Direction)

    Projection() = default;

    static void orthoDirections(Type type, Gx::Vec3 &up, Gx::Vec3 &right, Gx::Vec3 &forward);
    static Gx::Matrix orthoMatrix(Type type, const Gx::SizeF &size, const Gx::Vec3 &pos);

    static void clampOrthoZ(Type type, Gx::Vec3 &pos);

    static Gx::Transform camera(Type type);

    static const char *toString(Type type);
};

template<> struct qpx_is_meta_enum<Projection::Type> : std::true_type { };
template<> struct qpx_is_meta_enum<Projection::Direction> : std::true_type { };

#endif // PROJECTION_H
