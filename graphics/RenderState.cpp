#include "RenderState.h"

#include "graphics/Graphics.h"
#include "graphics/RenderParams.h"

#include <GxGraphics/GxVertexDeclaration.h>
#include <GxGraphics/GxShader.h>

RenderState::RenderState(Type type, Flags flags, Graphics *graphics, const RenderParams &params) : graphics(graphics)
{
    if(type == Type::Preview)
    {
        graphics->device.setVertexDeclaration(*graphics->previewVertexDec);

        graphics->device.setVertexShader(*graphics->previewShader);
        graphics->previewShader->setMatrix(graphics->device, "world", Gx::Matrix::identity());
        graphics->previewShader->setMatrix(graphics->device, "viewproj", params.view * params.proj);
        graphics->previewShader->setVector(graphics->device, "light", params.light);
    }
    else if(type == Type::Color)
    {
        graphics->device.setVertexDeclaration(*graphics->colorVertexDec);

        graphics->device.setVertexShader(*graphics->colorShader);
        graphics->colorShader->setMatrix(graphics->device, "worldviewproj", params.view * params.proj);

        graphics->device.setZBufferEnable(false);
        graphics->device.setPointSize(6.0f);
    }
    else if(type == Type::Screen)
    {
        graphics->device.setVertexDeclaration(*graphics->colorVertexDec);

        graphics->device.setVertexShader(*graphics->screenShader);
        graphics->screenShader->setFloat(graphics->device, "dx", params.size.width);
        graphics->screenShader->setFloat(graphics->device, "dy", params.size.height);

        graphics->device.setZBufferEnable(false);
    }

    if(flags & Flag::Invert)
    {
        graphics->device.setAlphaBlend(Gx::GraphicsDevice::AlphaBlend::Invert);
    }
}

RenderState::RenderState(RenderState &&r) : graphics(r.graphics)
{
    r.graphics = nullptr;
}

RenderState::~RenderState()
{
    if(graphics)
    {
        graphics->device.setZBufferEnable(true);
        graphics->device.setAlphaBlend(Gx::GraphicsDevice::AlphaBlend::Off);
    }
}

RenderState::operator bool() const
{
    return true;
}
