#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

#include <QGxMaths/QGxMathsMetatypes.h>

class TextureData
{
public:
    TextureData() : scale(1, 1), offset(0, 0) { }

    bool operator==(const TextureData &o) const { return scale == o.scale && offset == o.offset; }
    bool operator!=(const TextureData &o) const { return scale != o.scale || offset != o.offset; }
    bool operator<(const TextureData &o) const { return true; }

    Gx::Vec2 scale;
    Gx::Vec2 offset;
};

Q_DECLARE_METATYPE(TextureData)

inline QDataStream &operator<<(QDataStream &ds, const TextureData &v){ return ds << v.scale << v.offset; }
inline QDataStream &operator>>(QDataStream &ds, TextureData &v){ return ds >> v.scale >> v.offset; }

#endif // TEXTUREDATA_H
