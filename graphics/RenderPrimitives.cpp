#include "RenderPrimitives.h"

#include "graphics/Graphics.h"
#include "graphics/RenderState.h"

#include <GxMaths/GxVector.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>

void RenderPrimitives::invertBox(Graphics *graphics, const RenderParams &params, const Gx::Vec2 &anc, const Gx::Vec2 &pos)
{
    Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);
    auto color = Gx::Color(1, 1, 1);

    os << Gx::Vec3(anc.x, anc.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(pos.x, anc.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(pos.x, anc.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(pos.x, pos.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(pos.x, pos.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(anc.x, pos.y, 0) << Gx::Rgba(color);

    os << Gx::Vec3(anc.x, pos.y, 0) << Gx::Rgba(color);
    os << Gx::Vec3(anc.x, anc.y, 0) << Gx::Rgba(color);

    auto r = RenderState(RenderState::Type::Screen, RenderState::Flag::Invert | RenderState::Flag::NoZ | RenderState::Flag::NoZWrite, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, 4);
}

