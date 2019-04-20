#include "ModelMap.h"

#include "graphics/Graphics.h"

#include "models/Model.h"

#include <GxGraphics/GxVertexBuffer.h>

#include <GxGraphics/GxBufferStream.h>

#include <pcx/datastream.h>

#include <QtCore/QDir>

ModelMap::ModelMap(Model *model, Graphics *graphics, QObject *parent) : QObject(parent), model(model), graphics(graphics)
{
}

void ModelMap::add(const QString &file)
{
    QString path = model->property("Models").value<QString>() + QDir::separator() + file;

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
        pcx::data_ifstream ds(path.toStdString());
        if(!ds.is_open())
        {
            throw 0;
        }

        auto n = ds.get<unsigned>();

        v[index] = graphics->resources.add(new Gx::VertexBuffer());

        auto &vb = *v[index];
        vb.reset(graphics->device, { n, { }, Gx::Graphics::Pool::Managed });

        Gx::BufferStream<Gx::VertexBuffer> os(vb, Gx::Graphics::Lock::Flag::Discard);
        ds.read(os.data(), n);
    }

    catch(...)
    {
    }
}

void ModelMap::remove(const QString &file)
{
    auto index = m[file];

    v[index] = { };
    free.push_back(index);

    m.remove(file);
}

void ModelMap::clear()
{
    v.clear();
    m.clear();
    free.clear();
}
