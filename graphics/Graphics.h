#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QtCore/QObject>

#include <GxGraphics/GxGraphicsResource.h>

#include <QGxGraphics/QGxGraphicsDevice.h>

#include <pcx/resource_map.h>
#include <pcx/scoped_ptr.h>

namespace Gx
{

class VertexDeclaration;
class VertexShader;
class PixelShader;
class VertexBuffer;
class Texture;

}

class Graphics : public QObject
{
    Q_OBJECT

public:
    explicit Graphics(QObject *parent = nullptr);
    virtual ~Graphics() override;

    QGx::GraphicsDevice device;
    pcx::resource_map<Gx::GraphicsResource> resources;

    template<typename T> using Handle = pcx::resource_handle<Gx::GraphicsResource, T>;

    Handle<Gx::VertexDeclaration> previewVertexDec;
    Handle<Gx::VertexDeclaration> colorVertexDec;

    Handle<Gx::VertexShader> previewShader;
    Handle<Gx::VertexShader> colorShader;
    Handle<Gx::VertexShader> screenShader;
    Handle<Gx::VertexShader> ndcShader;

    Handle<Gx::PixelShader> previewPixelShader;

    Handle<Gx::VertexBuffer> genericBuffer;
    Handle<Gx::Texture> genericTexture;

signals:
    void render();
    void deviceReset();

private slots:
    void timeout();
};

#endif // GRAPHICS_H
