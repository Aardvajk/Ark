#ifndef RENDERPARAMS_H
#define RENDERPARAMS_H

#include <GxMaths/GxSize.h>
#include <GxMaths/GxVector.h>
#include <GxMaths/GxMatrix.h>

class RenderParams
{
public:
    RenderParams() = default;

    Gx::SizeF size;
    float fov;

    Gx::Matrix view;
    Gx::Matrix proj;

    Gx::Vec3 position;
    Gx::Vec3 light;
};

#endif // RENDERPARAMS_H