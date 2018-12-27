#include "Buffer.h"

#include <GxGraphics/GxGraphicsDevice.h>
#include <GxGraphics/GxVertexBuffer.h>

Buffer::Buffer(Graphics *graphics, std::uint32_t elements, std::uint16_t stride, QObject *parent) : QObject(parent), valid(false)
{
    handle = graphics->resources.add(new Gx::VertexBuffer(graphics->device, { elements, stride, Gx::Graphics::Usage::Flag::Dynamic, Gx::Graphics::Pool::Default }));

    connect(graphics, SIGNAL(deviceReset()), SLOT(invalidate()));
}

void Buffer::renderTriangleList(Gx::GraphicsDevice &device) const
{
    device.renderTriangleList(buffer(), count());
}

void Buffer::renderLineList(Gx::GraphicsDevice &device) const
{
    device.renderLineList(buffer(), count());
}

void Buffer::renderPointList(Gx::GraphicsDevice &device) const
{
    device.renderPointList(buffer(), count());
}

const Gx::VertexBuffer &Buffer::buffer() const
{
    checkValid();
    return *handle;
}

unsigned Buffer::count() const
{
    checkValid();
    return n;
}

void Buffer::invalidate()
{
    valid = false;
}

void Buffer::checkValid() const
{
    if(!valid)
    {
        n = 0;
        generate(*handle, n);

        valid = true;
    }
}
