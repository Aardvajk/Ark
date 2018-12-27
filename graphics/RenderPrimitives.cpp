#include "RenderPrimitives.h"

#include "graphics/Graphics.h"
#include "graphics/RenderState.h"

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

void RenderPrimitives::line(Graphics *graphics, const RenderParams &params, const Gx::Vec3 &start, const Gx::Vec3 &end, const Gx::Color &color)
{
    Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);

    os << start << Gx::Rgba(color);
    os << end << Gx::Rgba(color);

    auto r = RenderState(RenderState::Type::Color, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, 4);
}

void RenderPrimitives::box(Graphics *graphics, const RenderParams &params, const Gx::Vec2 &anc, const Gx::Vec2 &pos, const Gx::Color &color)
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

    auto r = RenderState(RenderState::Type::Screen, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, 4);
}

