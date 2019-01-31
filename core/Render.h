#ifndef RENDER_H
#define RENDER_H

#include <QPxCore/QPxMetaType.h>

#include <QtCore/QObject>

class Render : public QObject
{
    Q_OBJECT

public:
    enum class Type { Wireframe, Flat, Textured, None };
    Q_ENUM(Type)

    Render() = default;

    static const char *toString(Type type);
};

template<> struct qpx_is_meta_enum<Render::Type> : std::true_type { };

#endif // RENDER_H
