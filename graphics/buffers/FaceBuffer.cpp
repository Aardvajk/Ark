#include "FaceBuffer.h"

#include "graphics/vertices/PreviewVertex.h"

#include "graphics/components/EdgeKey.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "properties/custom/Mesh.h"
#include "properties/custom/Selection.h"

#include <GxMaths/GxVector.h>

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <QGxMaths/QGxColor.h>

FaceBuffer::FaceBuffer(Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535, sizeof(PreviewVertex), parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void FaceBuffer::generate(Gx::VertexBuffer &buffer, unsigned &count) const
{
    Gx::BufferStream<Gx::VertexBuffer> os(buffer, Gx::Graphics::Lock::Flag::Discard);

    for(const auto &e: model->entities())
    {
        if(e.type() == Entity::Type::Geometry)
        {
            auto mesh = e.properties()["Mesh"].value<Mesh>();
            auto sel = e.properties()["Selection"].value<Selection>();

            QSet<EdgeKey> edges;

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                if(sel.elements[Element::Type::Face].contains(i))
                {
                    auto &e = mesh.faces[i].elements;

                    for(int j = 0; j < e.count(); ++j)
                    {
                        edges.insert(EdgeKey(e[j].index, e[j == e.count() - 1 ? 0 : j + 1].index));
                    }
                }
            }

            auto c = Gx::Color(1.0f, 1.0f, 1.0f);

            for(auto &edge: edges)
            {
                os << mesh.vertices[edge.keys.first] << Gx::Rgba(c);
                os << mesh.vertices[edge.keys.second] << Gx::Rgba(c);

                ++count;
            }
        }
    }
}
