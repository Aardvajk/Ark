#include "RenderPrimitives.h"

#include "core/Mesh.h"

#include "graphics/Graphics.h"
#include "graphics/RenderParams.h"
#include "graphics/RenderState.h"

#include "graphics/components/EdgeKey.h"

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

void RenderPrimitives::screenBox(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec2 &anc, const Gx::Vec2 &pos, const Gx::Color &color)
{
    if(true)
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
    }

    if(auto r = RenderState(RenderState::Type::Screen, flags, graphics, params))
    {
        graphics->device.renderLineList(*graphics->genericBuffer, 4);
    }
}

void RenderPrimitives::screenCircle(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec2 &pos, float radius, int slices, const Gx::Color &color)
{
    int count = 0;

    if(true)
    {
        Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);
        Gx::Vec3 sp(pos.x, pos.y, 0);

        std::vector<Gx::Vec3> pts;
        for(float a = 0; a < M_PI * 2; a += (M_PI * 2) / slices)
        {
            pts.push_back(Gx::Vec3(sinf(a), cosf(a), 0));
        }

        for(std::size_t i = 0; i < pts.size(); ++i)
        {
            std::size_t j = i < pts.size() - 1 ? i + 1 : 0;

            os << sp + (pts[i] * radius) << Gx::Rgba(color);
            os << sp + (pts[j] * radius) << Gx::Rgba(color);

            ++count;
        }
    }

    if(auto r = RenderState(RenderState::Type::Screen, flags, graphics, params))
    {
        graphics->device.renderLineList(*graphics->genericBuffer, count);
    }
}

void RenderPrimitives::wireframeMesh(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Mesh &mesh, const Gx::Color &color)
{
    int count = 0;

    if(true)
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

        for(auto &edge: edges)
        {
            os << mesh.vertices[edge.keys.first] << Gx::Rgba(color);
            os << mesh.vertices[edge.keys.second] << Gx::Rgba(color);

            ++count;
        }
    }

    if(auto r = RenderState(RenderState::Type::Color, flags, graphics, params))
    {
        graphics->device.renderLineList(*graphics->genericBuffer, count);
    }
}

void RenderPrimitives::cursor(Graphics *graphics, const RenderParams &params, RenderState::Flags flags, const Gx::Vec3 &pos, const Gx::Color &color)
{
    int count = 0;

    if(true)
    {
        Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);
        auto sp = pos.transformedCoord(params.view * params.proj);

        if(sp.x >= -1 && sp.x <= 1)
        {
            os << Gx::Vec3(sp.x, -1, 0) << Gx::Rgba(color);
            os << Gx::Vec3(sp.x, 1, 0) << Gx::Rgba(color);

            ++count;
        }

        if(sp.y >= -1 && sp.y <= 1)
        {
            os << Gx::Vec3(-1, sp.y, 0) << Gx::Rgba(color);
            os << Gx::Vec3(1, sp.y, 0) << Gx::Rgba(color);

            ++count;
        }
    }

    if(auto r = RenderState(RenderState::Type::Ndc, flags, graphics, params))
    {
        graphics->device.renderLineList(*graphics->genericBuffer, count);
    }

    screenCircle(graphics, params, flags, Projection::worldToScreen(params, pos), 10.0f, 16, color);
}
