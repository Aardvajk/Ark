#include "PreviewBuffer.h"

#include "core/Mesh.h"

#include "properties/custom/TextureData.h"

#include "graphics/TextureCache.h"

#include "graphics/vertices/PreviewVertex.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <GxMaths/GxVector.h>

#include <QGxMaths/QGxColor.h>

#include <pcx/indexed_range.h>

PreviewBuffer::PreviewBuffer(Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535 * sizeof(PreviewVertex), parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void PreviewBuffer::render(Render::Type type, Graphics *graphics) const
{
    if(type == Render::Type::Flat)
    {
        renderTriangleList(graphics->device);
        return;
    }

    checkValid();

    for(auto key: sections.keys())
    {
        auto path = model->property("Textures").value<QString>();
        auto texture = key.diffuse;
        auto range = sections[key];

        if(!path.isEmpty() && !texture.isEmpty())
        {
            graphics->device.setTexture(0, graphics->textures->texture(path, texture));
        }

        renderTriangleList(graphics->device, range.first, range.second);

        graphics->device.setTexture(0);
    }
}

void PreviewBuffer::generate(Gx::VertexBuffer &buffer, unsigned &count) const
{
    QHash<RenderKey, QVector<QPair<int, int> > > mapping;

    for(auto e: pcx::indexed_range(model->entities()))
    {
        if(e.value.type() == Entity::Type::Geometry)
        {
            auto &mesh = e.value.mesh();

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                if(e.value.subProperty(Element::Type::Face, i, "Visible").value<bool>())
                {
                    RenderKey key;

                    key.group = e.value.property("Group").value<QString>();
                    key.diffuse = e.value.subProperty(Element::Type::Face, i, "Texture").value<TextureData>().source;

                    mapping[key].append(qMakePair(static_cast<int>(e.index), i));
                }
            }
        }
    }

    sections.clear();

    Gx::BufferStream<Gx::VertexBuffer> os(buffer, Gx::Graphics::Lock::Flag::Discard);

    unsigned start = 0;
    unsigned written = 0;

    for(auto key: mapping.keys())
    {
        for(auto pair: mapping[key])
        {
            auto &e = model->entities()[pair.first];
            auto &mesh = e.mesh();

            auto i = pair.second;

            auto c = QGx::Color(e.subProperty(Element::Type::Face, i, "Color").value<QColor>());

            for(int j = 1; j < mesh.faces[i].elements.count() - 1; ++j)
            {
                auto n = mesh.faceNormal(i);

                os << mesh.vertex(i, 0) << n << Gx::Rgba(c) << mesh.faces[i].elements[0].texCoords;
                os << mesh.vertex(i, j) << n << Gx::Rgba(c) << mesh.faces[i].elements[j].texCoords;
                os << mesh.vertex(i, j + 1) << n << Gx::Rgba(c) << mesh.faces[i].elements[j + 1].texCoords;

                ++written;
            }
        }

        sections[key] = qMakePair(start, written);

        count += written;

        start += written * 3;
        written = 0;
    }
}
