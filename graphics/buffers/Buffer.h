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
    Buffer(Graphics *graphics, std::uint32_t elements, std::uint16_t stride, QObject *parent = nullptr);

    void renderTriangleList(Gx::GraphicsDevice &device) const;
    void renderLineList(Gx::GraphicsDevice &device) const;
    void renderPointList(Gx::GraphicsDevice &device) const;

    const Gx::VertexBuffer &buffer() const;
    unsigned count() const;

public slots:
    void invalidate();

protected:
    virtual void generate(Gx::VertexBuffer &buffer, unsigned &count) const = 0;

private:
    void checkValid() const;

    mutable Graphics::Handle<Gx::VertexBuffer> handle;
    mutable unsigned n;
    mutable bool valid;
};

#endif // BUFFER_H
