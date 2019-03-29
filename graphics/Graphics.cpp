#include "Graphics.h"

#include <QtCore/QTimer>

#include "core/ResourcePath.h"

#include "graphics/TextureCache.h"

#include "graphics/vertices/PreviewVertex.h"
#include "graphics/vertices/ColorVertex.h"

#include <GxGraphics/GxShader.h>
#include <GxGraphics/GxVertexBuffer.h>
#include <GxGraphics/GxTexture.h>

#include <fstream>

namespace
{

std::vector<char> load(const std::string &path)
{
    std::ifstream is(path.c_str(), std::ios::binary);
    if(!is.is_open())
    {
        throw std::runtime_error("unable to open - " + path);
    }

    DWORD n;
    is.read(reinterpret_cast<char*>(&n), sizeof(DWORD));

    std::vector<char> bs(n);
    is.read(bs.data(), n);

    return bs;
}

}

Graphics::Graphics(QObject *parent) : QObject(parent)
{
    previewVertexDec = resources.add(new Gx::VertexDeclaration(device, PreviewVertex::declaration()));
    colorVertexDec = resources.add(new Gx::VertexDeclaration(device, ColorVertex::declaration()));

    previewShader = resources.add(new Gx::VertexShader(device, load(resourcePath("shaders/previewvertex.dat"))));
    colorShader = resources.add(new Gx::VertexShader(device, load(resourcePath("shaders/colorvertex.dat"))));
    screenShader = resources.add(new Gx::VertexShader(device, load(resourcePath("shaders/screenvertex.dat"))));
    ndcShader = resources.add(new Gx::VertexShader(device, load(resourcePath("shaders/ndcvertex.dat"))));

    previewPixelShader = resources.add(new Gx::PixelShader(device, load(resourcePath("shaders/previewpixel.dat"))));

    genericBuffer = resources.add(new Gx::VertexBuffer(device, { 25600 * sizeof(ColorVertex), Gx::Graphics::Usage::Flag::Dynamic, Gx::Graphics::Pool::Default }));
    genericTexture = resources.add(new Gx::Texture(device, resourcePath("assets/generic.png"), { { }, 0, { }, Gx::Graphics::Format::A8R8G8B8, Gx::Graphics::Pool::Managed }));

    textures = new TextureCache(genericTexture.get(), *this);

    auto timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(timeout()));

    timer->start(0);
}

Graphics::~Graphics() = default;

void Graphics::timeout()
{
    bool reset = false;

    if(!device.isOk())
    {
        if(!device.isReadyToReset()) return;
        reset = true;
    }

    if(device.needsResetting())
    {
        reset = true;
    }

    if(reset)
    {
        for(auto &r: resources) if(r.isDeviceBound()) r.release();
        device.reset();
        for(auto &r: resources) if(r.isDeviceBound()) r.reset(device);

        emit deviceReset();
    }

    emit render();
}
