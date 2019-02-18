#include "Graphics.h"

#include <QtCore/QTimer>

#include "graphics/vertices/PreviewVertex.h"
#include "graphics/vertices/ColorVertex.h"

#include <GxGraphics/GxShader.h>
#include <GxGraphics/GxVertexBuffer.h>

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

    previewShader = resources.add(new Gx::VertexShader(device, load("C:/Projects/Ark/Ark/previewvertex.dat")));
    colorShader = resources.add(new Gx::VertexShader(device, load("C:/Projects/Ark/Ark/colorvertex.dat")));
    screenShader = resources.add(new Gx::VertexShader(device, load("C:/Projects/Ark/Ark/screenvertex.dat")));
    ndcShader = resources.add(new Gx::VertexShader(device, load("C:/Projects/Ark/Ark/ndcvertex.dat")));

    genericBuffer = resources.add(new Gx::VertexBuffer(device, { 25600 * sizeof(ColorVertex), Gx::Graphics::Usage::Flag::Dynamic, Gx::Graphics::Pool::Default }));

    auto timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(timeout()));

    timer->start(0);
}

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
