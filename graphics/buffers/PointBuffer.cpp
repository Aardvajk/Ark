#include "PointBuffer.h"

#include "core/Selection.h"

#include "core/Mesh.h"

#include "graphics/vertices/ColorVertex.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include "core/Mesh.h"

#include <GxMaths/GxVector.h>

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <QtCore/QSet>

PointBuffer::PointBuffer(Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535, sizeof(ColorVertex), parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void PointBuffer::generate(Gx::VertexBuffer &buffer, unsigned &count) const
{
    Gx::BufferStream<Gx::VertexBuffer> os(buffer, Gx::Graphics::Lock::Flag::Discard);

    for(auto &e: model->entities())
    {
        if(e.type() == Entity::Type::Geometry)
        {
            auto &mesh = e.mesh();
            auto selection = e.selection();

            auto c = Gx::Color(1.0f, 1.0f, 1.0f);

            for(int i = 0; i < mesh.vertices.count(); ++i)
            {
                if(selection.elements[Element::Type::Vertex].contains(i))
                {
                    os << mesh.vertices[i] << Gx::Rgba(c);
                    ++count;
                }
            }
        }
    }
}
