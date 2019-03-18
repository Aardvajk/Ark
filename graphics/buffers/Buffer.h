#ifndef BUFFER_H
#define BUFFER_H

#include "graphics/Graphics.h"

#include <QtCore/QObject>

namespace Gx
{

class GraphicsDevice;
class VertexBuffer;

}

class Buffer : public QObject
{
    Q_OBJECT

public:
    Buffer(Graphics *graphics, std::uint32_t bytes, QObject *parent = nullptr);

    void renderTriangleList(Gx::GraphicsDevice &device) const;
    void renderLineList(Gx::GraphicsDevice &device) const;
    void renderPointList(Gx::GraphicsDevice &device) const;

    void renderTriangleList(Gx::GraphicsDevice &device, unsigned start, unsigned count) const;

    const Gx::VertexBuffer &buffer() const;
    unsigned count() const;

public slots:
    void invalidate();

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const = 0;

    void checkValid() const;

private:
    mutable Graphics::Handle<Gx::VertexBuffer> handle;
    mutable unsigned n;
    mutable bool valid;
};

#endif // BUFFER_H
