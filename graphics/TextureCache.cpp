#include "TextureCache.h"

#include <GxGraphics/GxTexture.h>

#include <QtCore/QDir>

namespace
{

QString textureId(const QString &path, const QString &file)
{
    return path + QDir::separator() + file;
}

}

TextureCache::TextureCache(const Gx::Texture *generic, Graphics &graphics) : graphics(graphics), generic(generic)
{
}

TextureCache::~TextureCache() = default;

const Gx::Texture &TextureCache::texture(const QString &path, const QString &file) const
{
    auto id = textureId(path, file);

    auto i = m.find(id);
    if(i == m.end())
    {
        try
        {
            v.push_back(graphics.resources.add(new Gx::Texture(graphics.device, id.toStdString(), { { }, 0, { }, Gx::Graphics::Format::A8R8G8B8, Gx::Graphics::Pool::Managed })));
            m[id] = v.back().get();

            return *m[id];
        }

        catch(...)
        {
            return *generic;
        }
    }

    return *i.value();
}

