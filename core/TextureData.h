#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

#include <QGxMaths/QGxMathsMetatypes.h>

class TextureData
{
public:
    TextureData() : scale(1, 1) { }
    explicit TextureData(const Gx::Vec2 &scale) : scale(scale) { }

    bool operator==(const TextureData &o) const { return scale == o.scale; }
    bool operator!=(const TextureData &o) const { return scale != o.scale; }
    bool operator<(const TextureData &o) const { return true; }

    Gx::Vec2 scale;
};

Q_DECLARE_METATYPE(TextureData)

inline QDataStream &operator<<(QDataStream &ds, const TextureData &v){ return ds << v.scale; }
inline QDataStream &operator>>(QDataStream &ds, TextureData &v){ return ds >> v.scale; }

#endif // TEXTUREDATA_H
