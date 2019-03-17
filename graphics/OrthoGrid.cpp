#include "OrthoGrid.h"

#include "maths/Projection.h"

#include "graphics/Graphics.h"
#include "graphics/RenderParams.h"
#include "graphics/RenderState.h"

#include <GxMaths/GxViewport.h>
#include <GxMaths/GxColor.h>

#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxBufferStream.h>


namespace
{

Gx::Vec3 swizzle(Projection::Type type, const Gx::Vec3 &v)
{
    switch(type)
    {
        case Projection::Type::Top:
        case Projection::Type::Bottom: return Gx::Vec3(v.x, v.z, v.y);

        case Projection::Type::Left:
        case Projection::Type::Right: return Gx::Vec3(v.z, v.y, v.x);

        default: return v;
    }
}

struct Measure
{
    Gx::Vec2 pos;
    Gx::Vec2 dims;
};

Measure measure(const Gx::Vec3 &min, const Gx::Vec3 &max, float grid)
{
    Measure m;

    m.pos.x = min.x - fmod(min.x, grid);
    m.pos.y = min.y - fmod(min.y, grid);

    m.dims.x = (max.x - m.pos.x) / grid;
    m.dims.y = (max.y - m.pos.y) / grid;

    return m;
}

}

void renderOrthoGrid(Graphics *graphics, const RenderParams &params, float grid, const Gx::Color &color)
{
    auto min = swizzle(params.projection, Gx::Vec3(0, 0, 0).unprojected(Gx::Viewport(params.size), Gx::Matrix::identity(), params.view, params.proj));
    auto max = swizzle(params.projection, Gx::Vec3(params.size.width, params.size.height, 0).unprojected(Gx::Viewport(params.size), Gx::Matrix::identity(), params.view, params.proj));

    if(min.x > max.x) qSwap(min.x, max.x);
    if(min.y > max.y) qSwap(min.y, max.y);

    Gx::BufferStream<Gx::VertexBuffer> os(*graphics->genericBuffer, Gx::Graphics::Lock::Flag::Discard);

    auto m = measure(min, max, grid);
    while(m.dims.x > 50 || m.dims.y > 50)
    {
        grid *= 10;
        m = measure(min, max, grid);
    }

    int n = 0;

    for(;m.pos.x < max.x; m.pos.x += grid, ++n)
    {
        os << swizzle(params.projection, Gx::Vec3(m.pos.x, min.y, 1)) << Gx::Rgba(color);
        os << swizzle(params.projection, Gx::Vec3(m.pos.x, max.y, 1)) << Gx::Rgba(color);
    }

    for(;m.pos.y < max.y; m.pos.y += grid, ++n)
    {
        os << swizzle(params.projection, Gx::Vec3(min.x, m.pos.y, 1)) << Gx::Rgba(color);
        os << swizzle(params.projection, Gx::Vec3(max.x, m.pos.y, 1)) << Gx::Rgba(color);
    }

    auto r = RenderState(RenderState::Type::Color, RenderState::Flag::NoZ | RenderState::Flag::NoZWrite, graphics, params);
    graphics->device.renderLineList(*graphics->genericBuffer, 0, n);
}
