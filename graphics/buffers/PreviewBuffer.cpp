#include "PreviewBuffer.h"

#include "graphics/vertices/PreviewVertex.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <GxMaths/GxVector.h>

#include <QGxMaths/QGxColor.h>

#include "physics/Mesh.h"

PreviewBuffer::PreviewBuffer(Model *model, Graphics *graphics, QObject *parent) : Buffer(graphics, 65535, sizeof(PreviewVertex), parent), model(model)
{
    connect(model, SIGNAL(changed()), SLOT(invalidate()));
}

void PreviewBuffer::generate(Gx::VertexBuffer &buffer, unsigned &count) const
{
    Gx::BufferStream<Gx::VertexBuffer> os(buffer, Gx::Graphics::Lock::Flag::Discard);

    for(const auto &e: model->entities())
    {
        if(e.type() == Entity::Type::Geometry)
        {
            auto &mesh = e.mesh();

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                if(e.subProperty(Element::Type::Face, i, "Visible").value<bool>())
                {
                    auto c = QGx::Color(e.subProperty(Element::Type::Face, i, "Color").value<QColor>());

                    for(int j = 1; j < mesh.faces[i].elements.count() - 1; ++j)
                    {
                        auto n = mesh.faceNormal(i);

                        os << mesh.vertex(i, 0) << n << Gx::Rgba(c);
                        os << mesh.vertex(i, j) << n << Gx::Rgba(c);
                        os << mesh.vertex(i, j + 1) << n << Gx::Rgba(c);

                        ++count;
                    }
                }
            }
        }
    }
}
