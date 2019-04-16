#include "PreviewBuffer.h"

#include "core/Mesh.h"

#include "properties/custom/TextureData.h"

#include "graphics/vertices/PreviewVertex.h"

#include "models/Model.h"
#include "models/TextureMap.h"

#include "maths/Tangent.h"

#include "entity/Entity.h"

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>
#include <GxGraphics/GxShader.h>

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
        auto diffuse = key.diffuse;
        auto normal = key.normal;
        auto range = sections[key];

        if(!diffuse.isEmpty())
        {
            graphics->device.setTexture(0, model->textures().texture(diffuse));
            graphics->previewPixelShader->setBool(graphics->device, "diffuseEnabled", true);
        }
        else
        {
            graphics->previewPixelShader->setBool(graphics->device, "diffuseEnabled", false);
        }

        if(!normal.isEmpty())
        {
            graphics->device.setTexture(1, model->textures().texture(normal));
            graphics->previewPixelShader->setBool(graphics->device, "normalEnabled", true);
        }
        else
        {
            graphics->previewPixelShader->setBool(graphics->device, "normalEnabled", false);
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
                    key.diffuse = e.value.subProperty(Element::Type::Face, i, "Texture").value<TextureData>().diffuse;
                    key.normal = e.value.subProperty(Element::Type::Face, i, "Texture").value<TextureData>().normal;
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

                auto &f = mesh.faces[i];

                auto tn = calculateTangent(mesh.vertex(i, 0), f.elements[0].texCoords, mesh.vertex(i, j), f.elements[j].texCoords, mesh.vertex(i, j + 1), f.elements[j + 1].texCoords, n);

                os << mesh.vertex(i, 0) << n << Gx::Rgba(c) << f.elements[0].texCoords << tn;
                os << mesh.vertex(i, j) << n << Gx::Rgba(c) << f.elements[j].texCoords << tn;
                os << mesh.vertex(i, j + 1) << n << Gx::Rgba(c) << f.elements[j + 1].texCoords << tn;

                ++written;
            }
        }

        sections[key] = qMakePair(start, written);

        count += written;

        start += written * 3;
        written = 0;
    }
}
