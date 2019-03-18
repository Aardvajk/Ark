#include "TextureCache.h"

#include <GxGraphics/GxTexture.h>

#include <QtCore/QDir>

namespace
{

QString textureId(const QString &path, const QString &file)
{
    return path + QDir::separator() + file;
}

Graphics::Handle<Gx::Texture> makeTexture(Graphics &graphics, const QString &id)
{
    return graphics.resources.add(new Gx::Texture(graphics.device, id.toStdString(), { { }, 0, { }, Gx::Graphics::Format::A8R8G8B8, Gx::Graphics::Pool::Managed }));
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
            if(!free.empty())
            {
                auto index = free.back();
                free.pop_back();

                v[index] = makeTexture(graphics, id);
                m[id] = index;
            }
            else
            {
                v.push_back(makeTexture(graphics, id));
                m[id] = v.size() - 1;
            }

            return *v[m[id]];
        }

        catch(...)
        {
            return *generic;
        }
    }

    return *v[i.value()];
}
