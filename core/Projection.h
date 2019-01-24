#ifndef PROJECTION_H
#define PROJECTION_H

#include <QPxCore/QPxMetaType.h>

#include <GxMaths/GxMatrix.h>

#include <QtCore/QObject>

class RenderParams;

class Projection : public QObject
{
    Q_OBJECT

public:
    enum class Type { Perspective, Orthographic, None };
    Q_ENUM(Type)

    Projection() = default;

    static Gx::Matrix matrix(const RenderParams &params);
    static const char *toString(Type type);
};

template<> struct qpx_is_meta_enum<Projection::Type> : std::true_type { };

#endif // PROJECTION_H
