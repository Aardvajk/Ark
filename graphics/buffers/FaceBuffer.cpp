#include "FaceBuffer.h"

#include "graphics/vertices/ColorVertex.h"

#include "graphics/components/EdgeKey.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "properties/custom/Mesh.h"
#include "properties/custom/Selection.h"

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <QtCore/QSet>

FaceBuffer::FaceBuffer(Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535, sizeof(ColorVertex), parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void FaceBuffer::generate(Gx::VertexBuffer &buffer, unsigned &count) const
{
    Gx::BufferStream<Gx::VertexBuffer> os(buffer, Gx::Graphics::Lock::Flag::Discard);

    for(auto &e: model->entities())
    {
        if(e.type() == Entity::Type::Geometry)
        {
            auto mesh = e.properties()["Mesh"].toMesh();
            auto sel = e.properties()["Selection"].toSelection();

            QSet<EdgeKey> edges;

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                if(sel.object || sel.faces.contains(i))
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
