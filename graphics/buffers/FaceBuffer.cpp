#include "FaceBuffer.h"

#include "core/Selection.h"

#include "graphics/vertices/PreviewVertex.h"

#include "graphics/components/EdgeKey.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "core/Mesh.h"

#include <GxMaths/GxVector.h>

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <QGxMaths/QGxColor.h>

FaceBuffer::FaceBuffer(Type type, Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535 * sizeof(PreviewVertex), parent), type(type), model(model)
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
            auto &mesh = e.mesh();
            auto selection = e.selection();

            QSet<EdgeKey> edges;

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                bool selected = selection.elements[Element::Type::Face].contains(i);
                if(type == Type::Wireframe || selected)
                {
                    auto &e = mesh.faces[i].elements;

                    for(int j = 0; j < e.count(); ++j)
                    {
                        auto key = EdgeKey(e[j].index, e[j == e.count() - 1 ? 0 : j + 1].index, selected);

                        auto edge = edges.find(key);
                        if(edge == edges.end())
                        {
                            edges.insert(key);
                        }
                        else if(selected)
                        {
                            edges.remove(key);
                            edges.insert(key);
                        }
                    }
                }
            }

            auto color = Gx::Color(1.0f, 0.0f, 0.0f);

            for(auto &edge: edges)
            {
                auto c = color;
                if(type == Type::Wireframe && !edge.selected)
                {
                    c = Gx::Color(1.0f, 1.0f, 1.0f);
                }

                os << mesh.vertices[edge.keys.first] << Gx::Rgba(c);
                os << mesh.vertices[edge.keys.second] << Gx::Rgba(c);

                ++count;
            }
        }
    }
}
