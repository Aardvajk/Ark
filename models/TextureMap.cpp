#include "TextureMap.h"

#include "graphics/Graphics.h"

#include "models/Model.h"

#include <GxGraphics/GxTexture.h>

#include <QtCore/QDir>

TextureMap::TextureMap(Model *model, Graphics *graphics, QObject *parent) : QObject(parent), model(model), graphics(graphics)
{
}

void TextureMap::add(const QString &file)
{
    QString path = model->property("Textures").value<QString>() + QDir::separator() + file;

    std::size_t index;

    if(!free.isEmpty())
    {
        index = free.back();
        free.pop_back();
    }
    else
    {
        index = v.size();
        v.push_back({ });
    }

    m[file] = index;

    try
    {
        v[index] = graphics->resources.add(new Gx::Texture(graphics->device, path.toStdString(), { { }, 0, { }, Gx::Graphics::Format::A8R8G8B8, Gx::Graphics::Pool::Managed }));
    }

    catch(...)
    {
    }
}

void TextureMap::remove(const QString &file)
{
    auto index = m[file];

    v[index] = { };
    free.push_back(index);

    m.remove(file);
}

void TextureMap::clear()
{
    v.clear();
    m.clear();
    free.clear();
}

const Gx::Texture &TextureMap::texture(const QString &file) const
{
    auto i = m.find(file);
    if(i == m.end())
    {
        return *graphics->genericTexture;
    }

    return *v[i.value()];
}
