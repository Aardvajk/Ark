#include "PreviewBuffer.h"

#include "graphics/vertices/PreviewVertex.h"

#include "models/Model.h"

#include "entity/Entity.h"

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

#include <GxMaths/GxVector.h>
#include <GxMaths/GxMatrix.h>

#include <QGxMaths/QGxColor.h>

#include "properties/custom/Mesh.h"

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
            auto mesh = e.properties()["Mesh"].value<Mesh>();
            auto transform = Gx::Matrix::translation(e.properties()["Position"].value<Gx::Vec3>());

            for(int i = 0; i < mesh.faces.count(); ++i)
            {
                const auto &props = e.subProperties()[Element::Type::Face][i];

                if(props["Visible"].value<bool>())
                {
                    auto c = QGx::Color(props["Color"].value<QColor>());

                    for(int j = 1; j < mesh.faces[i].elements.count() - 1; ++j)
                    {
                        auto n = mesh.faceNormal(i);

                        os << mesh.vertex(i, 0).transformedCoord(transform) << n << Gx::Rgba(c);
                        os << mesh.vertex(i, j).transformedCoord(transform) << n << Gx::Rgba(c);
                        os << mesh.vertex(i, j + 1).transformedCoord(transform) << n << Gx::Rgba(c);

                        ++count;
                    }
                }
            }
        }
    }
}
