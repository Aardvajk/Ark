#include "RenderPrimitives.h"

#include "core/Mesh.h"

#include "graphics/Graphics.h"
#include "graphics/RenderState.h"

#include "graphics/components/EdgeKey.h"

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

void RenderPrimitives::screenBox(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec2 &anc, const Gx::Vec2 &pos, const Gx::Color &color)
{
    Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);

    os << Gx::Vec3(anc.x, anc.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(pos.x, anc.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(pos.x, anc.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(pos.x, pos.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(pos.x, pos.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(anc.x, pos.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(anc.x, pos.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(anc.x, anc.y, 0) << Gx::Rgba(color);

    auto r = RenderState(RenderState::Type::Screen, flags, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, 4);
}

void RenderPrimitives::wireframeMesh(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Mesh &mesh, const Gx::Color &color)
{
    Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);

    QSet<EdgeKey> edges;

    for(int i = 0; i < mesh.faces.count(); ++i)
    {
        auto &e = mesh.faces[i].elements;
        for(int j = 0; j < e.count(); ++j)
        {
            edges.insert(EdgeKey(e[j].index, e[j == e.count() - 1 ? 0 : j + 1].index));
        }
    }

    int count = 0;

    for(auto &edge: edges)
    {
        os << mesh.vertices[edge.keys.first] << Gx::Rgba(color);
        os << mesh.vertices[edge.keys.second] << Gx::Rgba(color);

        ++count;
    }

    auto r = RenderState(RenderState::Type::Color, flags, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, count);
}
