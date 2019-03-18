#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "graphics/Graphics.h"

#include <QtCore/QHash>

#include <vector>

class TextureCache
{
public:
    TextureCache(const Gx::Texture *generic, Graphics &graphics);
    ~TextureCache();

    const Gx::Texture &texture(const QString &path, const QString &file) const;

private:
    Graphics &graphics;
    const Gx::Texture *generic;

    mutable std::vector<Graphics::Handle<Gx::Texture> > v;
    mutable std::vector<std::size_t> free;

    mutable QHash<QString, std::size_t> m;
};

#endif // TEXTURECACHE_H
